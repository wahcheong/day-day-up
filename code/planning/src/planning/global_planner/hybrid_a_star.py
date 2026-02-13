# -*- coding: utf-8 -*-

import math
import queue
import time
from planning.utils.math_utils import normalize_angle

HYBRID_A_STAR_CONFIG = {
    "step_size": 0.5,  # meters
    "steering_angle_step_size": 0.1,  # radians, about 5.7 degrees
    "xy_resolution": 0.2,  # meters
    "heading_resolution": 0.1,  # radians, about 5.7 degrees
    "xy_tolerance": 0.2,  # meters
    "heading_tolerance": 0.2,  # radians, about 5.7 degrees
    "cost_of_forward_motion": 1.0,  # cost per meter for forward motion
    "cost_of_reverse_motion": 1.5,  # cost per meter for reverse motion
    "cost_of_gear_change": 2.0,  # penalty for changing gear direction
    "cost_of_steering": 0.5,  # penalty for steering
    "cost_of_steering_change": 0.1,  # penalty for steering changes
    "roi_margin": 20.0,  # meters
    "max_search_iterations": 10000000,  # maximum number of nodes to explore
    "max_search_time": 25.0,  # seconds
}

VEHICLE_PARAMS = {
    "wheelbase": 2.5,  # meters
    "max_steering_angle": math.radians(45),  # radians
}


class Node:
    def __init__(self, x, y, heading, gear=1, g=0.0, h=0.0, parent=None):
        """
        Initialize a node for the Hybrid A* algorithm.

        :param x: X position in meters
        :param y: Y position in meters
        :param heading: Heading angle in radians
        :param gear: 1 for forward, -1 for reverse
        :param id: ID for this node
        :param g: Cost from start to this node
        :param h: Heuristic cost from this node to goal
        :param parent: Parent node
        """
        self.x = x
        self.y = y
        self.heading = heading
        self.gear = gear
        self.id = None
        self.g = g  # Cost from start to this node
        self.h = h  # Heuristic cost from this node to goal
        self.f = g + h  # Total cost
        self.parent = parent

    def __eq__(self, other):
        return self.id == other.id

    def __hash__(self):
        return hash(self.id)

    def __lt__(self, other):
        return self.f < other.f

    def __repr__(self):
        return f"Node(x={self.x:.2f}, y={self.y:.2f}, heading={self.heading:.2f}, g={self.g:.2f}, h={self.h:.2f}, f={self.f:.2f})"

    def __str__(self):
        return f"Node(x={self.x:.2f}, y={self.y:.2f}, heading={self.heading:.2f}, g={self.g:.2f}, h={self.h:.2f}, f={self.f:.2f})"


class HybridAStar:
    def __init__(self, start, goal, vehicle_params=None, config=None):
        """
        Initialize the Hybrid A* planner.

        :param start: Start node (Node object)
        :param goal: Goal node (Node object)
        :param vehicle_params: Dictionary with vehicle parameters (e.g., wheelbase, max steering angle)
        :param config: Hyperparameters for the algorithm (e.g., step size, steering angle discretization)
        """
        if vehicle_params is None:
            raise ValueError("Vehicle parameters must be provided.")
        if config is None:
            raise ValueError("HybridAStar configuration must be provided.")
        self.start = start
        self.goal = goal
        self.vehicle_params = vehicle_params
        self.config = config
        self.roi_x_min = min(start.x, goal.x) - config["roi_margin"]
        self.roi_x_max = max(start.x, goal.x) + config["roi_margin"]
        self.roi_y_min = min(start.y, goal.y) - config["roi_margin"]
        self.roi_y_max = max(start.y, goal.y) + config["roi_margin"]
        self.start.id = self.compute_id(start.x, start.y, start.heading)
        self.goal.id = self.compute_id(goal.x, goal.y, goal.heading)
        self.priority_queue = queue.PriorityQueue()
        self.closed_set = set()
        self.path = []
        self.explored_nodes = []

    def heuristic(self, node):
        """
        Compute the heuristic cost from the current node to the goal.

        :param node: Current node (Node object)
        :return: Heuristic cost (float)
        """
        # TODO: Consider using Dubins path length as heuristic
        euclidean_distance = math.hypot(node.x - self.goal.x, node.y - self.goal.y)
        heading_penalty = abs(node.heading - self.goal.heading)
        return euclidean_distance + heading_penalty

    def compute_id(self, x, y, heading):
        """
        Compute a unique ID for a node based on its position and heading.

        :param x: X position in meters
        :param y: Y position in meters
        :param heading: Heading angle in radians
        :return: Unique ID (tuple)
        """
        x_id = int((x - self.roi_x_min) / self.config["xy_resolution"])
        y_id = int((y - self.roi_y_min) / self.config["xy_resolution"])
        heading_id = int((heading + math.pi) / self.config["heading_resolution"])
        return (x_id, y_id, heading_id)

    def is_collision_free(self, node):
        """
        Check if the given node is collision free.
        :param node: Current node (Node object)
        """
        # TODO: Collison check with obstacles
        return True

    def get_neighbors(self, node):
        """
        Generate neighboring nodes based on vehicle dynamics.
        :param node: Current node (Node object)
        :return: List of neighboring nodes
        """
        neighbors = []
        step_size = self.config["step_size"]
        steering_angle_step_size = self.config["steering_angle_step_size"]
        steering_angles_num = (
            int(
                (2 * self.vehicle_params["max_steering_angle"])
                / steering_angle_step_size
            )
            + 1
        )
        steering_angles = [
            float(r)
            for r in np.linspace(
                -self.vehicle_params["max_steering_angle"],
                self.vehicle_params["max_steering_angle"],
                num=steering_angles_num,
            )
        ]
        for delta in steering_angles:
            for gear in [1, -1]:
                new_heading = node.heading + gear * (
                    step_size / self.vehicle_params["wheelbase"]
                ) * math.tan(delta)
                new_heading = normalize_angle(new_heading)
                new_x = node.x + gear * step_size * math.cos(new_heading)
                new_y = node.y + gear * step_size * math.sin(new_heading)
                # Check if new position is within ROI
                if not (
                    self.roi_x_min <= new_x <= self.roi_x_max
                    and self.roi_y_min <= new_y <= self.roi_y_max
                ):
                    continue

                if gear == 1:
                    g_cost = node.g + step_size * self.config["cost_of_forward_motion"]
                else:
                    g_cost = node.g + step_size * self.config["cost_of_reverse_motion"]
                # Penalize steering changes
                g_cost += abs(delta) * self.config["cost_of_steering"]
                # Penalize gear changes
                if node.gear != gear:
                    g_cost += self.config["cost_of_gear_change"]

                h_cost = self.heuristic(Node(new_x, new_y, new_heading))
                neighbors.append(
                    Node(new_x, new_y, new_heading, gear, g_cost, h_cost, node)
                )
                neighbors[-1].id = self.compute_id(new_x, new_y, new_heading)
        return neighbors

    def reach_goal(self, node):
        """
        Check if the current node is close enough to the goal.

        :param node: Current node (Node object)
        :return: True if close to goal, False otherwise
        """
        return (
            abs(node.x - self.goal.x) < self.config["xy_tolerance"]
            and abs(node.y - self.goal.y) < self.config["xy_tolerance"]
            and abs(normalize_angle(node.heading - self.goal.heading))
            < self.config["heading_tolerance"]
        )

    def reconstruct_path(self, node):
        """
        Reconstruct the path from start to goal.

        :param node: Goal node (Node object)
        :return: List of nodes representing the path from start to goal
        """
        path = []
        while node:
            path.append(node)
            node = node.parent
        path.reverse()
        return path

    def search(self):
        """
        Perform the Hybrid A* search to find a path from start to goal.

        :return: List of nodes representing the path from start to goal
        """
        start_time = time.time()
        iterations = 0

        self.priority_queue.put((self.start.f, self.start))

        while not self.priority_queue.empty():
            iterations += 1
            if iterations > self.config["max_search_iterations"]:
                print(
                    f"Reached maximum search iterations({self.config['max_search_iterations']})"
                )
                return None
            if time.time() - start_time > self.config["max_search_time"]:
                print(f"Reached maximum search time({self.config['max_search_time']}s)")
                return None

            _, current = self.priority_queue.get()
            # Skip already evaluated nodes, as they may be re-added to the queue
            if current.id in self.closed_set:
                continue
            self.explored_nodes.append(current)
            if self.reach_goal(current):
                self.path = self.reconstruct_path(current)
                print(
                    f"Path found in {iterations} iterations and {time.time() - start_time:.2f} seconds."
                )
                return self.path
            self.closed_set.add(current.id)
            neighbors = self.get_neighbors(current)
            for neighbor in neighbors:
                if neighbor.id in self.closed_set:
                    # Skip already evaluated nodes
                    continue
                self.priority_queue.put((neighbor.f, neighbor))

        print(
            f"No path found within the given constraints after {iterations} iterations."
        )
        return None


if __name__ == "__main__":
    import numpy as np

    # Define start and goal nodes
    start_node = Node(x=0.0, y=0.0, heading=0.0)
    goal_node = Node(x=20.0, y=20.0, heading=0.0)

    # Initialize Hybrid A* planner
    planner = HybridAStar(
        start=start_node,
        goal=goal_node,
        vehicle_params=VEHICLE_PARAMS,
        config=HYBRID_A_STAR_CONFIG,
    )

    # Perform search
    path = planner.search()
    explored_nodes = planner.explored_nodes
    # Visualize the path using matplotlib
    if path:
        import matplotlib.pyplot as plt

        # Visualize the path and explored nodes
        x_path = [node.x for node in path]
        y_path = [node.y for node in path]
        x_explored = [node.x for node in explored_nodes]
        y_explored = [node.y for node in explored_nodes]
        headings = [node.heading for node in explored_nodes]
        plt.scatter(
            x_explored, y_explored, c=headings, cmap="hsv", marker=".", alpha=0.5
        )
        plt.plot(x_path, y_path, marker="o", color="red", linewidth=2, markersize=5)
        plt.colorbar(label="Heading (radians)")
        plt.title("Hybrid A* Path with Explored Nodes")
        plt.xlabel("X (meters)")
        plt.ylabel("Y (meters)")
        plt.grid()
        plt.axis("equal")
        plt.show()
    else:
        print("No path found.")
        # Optionally visualize explored nodes
        import matplotlib.pyplot as plt

        x_explored = [node.x for node in explored_nodes]
        y_explored = [node.y for node in explored_nodes]
        headings = [node.heading for node in explored_nodes]
        plt.scatter(x_explored, y_explored, c=headings, cmap="hsv", marker=".")
        plt.colorbar(label="Heading (radians)")
        plt.title("Explored Nodes")
        plt.xlabel("X (meters)")
        plt.ylabel("Y (meters)")
        plt.grid()
        plt.axis("equal")
        plt.show()
