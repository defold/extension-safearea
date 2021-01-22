# safearea

Simple native extension library for Defold that will change the view/render of a game to fit into the safe area on newer iPhones.

## Usage:

### Easy mode (no change to your project)

Just add the library to your project. The library will automatically resize the view on app start.

You can configure the color used outside the view by setting the `game.project` setting `safearea.background_*` values, for example;
```
[safearea]
background_red = 0.0
background_green = 1.0
background_blue = 0.0
```
This would make the background outside the safe area be **green**. (The default background color is black).


### Custom mode

Add the library to your project and set `safearea.resize_game_view` to `0` in your `game.project`:

```
[safearea]
resize_game_view = 0
```

This will disable the "Easy mode" behaviour and make the game view fill the whole screen (like Defold's default behaviour).

Now you can use `safearea.get_insets()` to query the extent of the safe area:

```lua
local insets = safearea.get_insets()

-- The amount of "unsafe" space against each edge of the screen, in pixels
print(insets.top, insets.right, insets.bottom, insets.left) 
```

