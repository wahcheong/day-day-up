#include "builder.h"

int main() {
  BubbleTea bubbleTea = BubbleTea::Builder()
                            .setBase(BubbleTea::BLACK_TEA)
                            .setSweetness(BubbleTea::LESS_SUGAR)
                            .setIce(BubbleTea::NORMAL_ICE)
                            .addTopping(BubbleTea::PEARLS)
                            .addTopping(BubbleTea::PUDDING)
                            .build();
  bubbleTea.display();

  return 0;
}
