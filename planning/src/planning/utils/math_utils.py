#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math


def normalize_angle(angle):
    """Normalize an radian angle to the range [-pi, pi)."""
    return (angle + math.pi) % (2 * math.pi) - math.pi
