# safearea

Simple native extension library for Defold that will change the view/render of a game to fit into the safe area on newer iPhones.

## Usage:
Just add the library to your project. The library will automatically resize the view on app start.

You can configure the color used outside the view by setting the `game.project` setting `safearea.background_*` values, for example;
```
[safearea]
background_red = 0.0
background_green = 1.0
background_blue = 0.0
```
This would make the background outside the safe area to **green**. (The default background color is black).
