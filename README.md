# Pendulum
That's my very first project for school science fair. It's the simulation of pendulum with the ability for editing the parameters such as length of the rope, initial speed so you can see how it works and affects on pendulum motion. It also contains graphs for better understanding. It's fully written on C++, SFML.

## What can it do?
  Basically, it's just the adjustable pendulum. It swings. The best part is that you can adjust parameters and see graphs.
  Parameters:
  - Length of the rope: arrow up/down to lengthen/shorten the rope. You can see how it affects pendulum's period.
  - Initial position: arrow right/left to increase/decrease the initial angle. There may be some bugs on the top of the pendulum (angle = pi), I tried to fix it. Also you can adjust the angle with mouse, but it works strange.
  - Damp: damping parameter is 0 by default. Use W/S to increase/decrease the damping. You may use R to reset it.
  - Graph window: Click the button, and you can see:
    * (time, angle) graph. It's sinusoidal at tiny angles, but gets less and less sinusoidal as the angle increases (just like in real life!) Also it gets e^(-ax)sin(x) graph as the damping increases or decreases. 
    * Energy bar graph: Red bar is Kinetic, green bar is potential energy. You can see that it increases/decreases as the initial angle increases or decreases. There is little gray line that shows the total energy. It stays almost same always what proves the energy conservation. It dangles a bit due to computing error. And remember: it's all just code!!!
    * (angle, angular velocity) graph. It's the incredible illustration for pendulum. It's a closed cycle: it's stable and periodic motion. There are some so-called "fixed points" where those ellipses you see collide: these are the top of the pendulum contour! It's all cyclic: The period of pendulum refreshes after every 2π! it slowly goes to middle, but never reaches (0,0) - it's damping exponentially! it leaves ellipse cycle - it goes bigger flow - it's the pendulum had the critical angular velocity so it swings without stopping - reaching the zero of angular velocity. You can play around with it with parameter and so on!
  ## How was it written?
  This code was fully written on c++17, with SFML 2.19 on XCode. I spent approximately a month to fully write it because was learning the SFML by the process.

  Thank you, have fun!
