---
title: SafeArea extension
brief: Extension to change the view of a game to fit into the safe area on iOS and Android devices with notch.
---

# SafeArea

Simple native extension library for Defold that will change the view/ of a game to fit into the safe area on iOS and Android devices with notch.

NOTE: Works on Android phones with API 28+.

## Installation
To use this library in your Defold project, add the following URL to your `game.project` dependencies:

[https://github.com/defold/extension-safearea/archive/master.zip](https://github.com/defold/extension-safearea/archive/master.zip)

We recommend using a link to a zip file of a [specific release](https://github.com/defold/extension-safearea/releases).

## Usage:

### Easy mode (no change to your project, iOS only)

Just add the library to your project. The library will automatically resize the view on app start.

You can configure the color used outside the view by setting the `game.project` setting `safearea.background_*` values, for example;
```
[safearea]
background_red = 0.0
background_green = 1.0
background_blue = 0.0
```
This would make the background outside the safe area be **green**. (The default background color is black).

It's also possible to change background color in runtime using `safearea.set_background_color(vmath.vector4())`.


### Custom mode

Add the library to your project and set `safearea.resize_game_view` to `0` in your `game.project`:

```
[safearea]
resize_game_view = 0
```

This will disable the "Easy mode" behaviour and make the game view fill the whole screen (like Defold's default behaviour).

Now you can use `safearea.get_insets()` to query the extent of the safe area:

```lua
local insets, status = safearea.get_insets()

-- The amount of "unsafe" space against each edge of the screen, in pixels
print(insets.top, insets.right, insets.bottom, insets.left)

-- iOS only
safearea.set_background_color(vmath.vector4(0,0,0,0))

-- Status is one of the following values:
-- safearea.STATUS_OK - value is avaliable and valid, you may fully trust it.
-- safearea.STATUS_NOT_AVAILABLE - functionality isn't available on this platform or OS version. Values will be 0
-- safearea.STATUS_NOT_READY_YET - values aren't ready yet. Depends on platform and OS it may take a while (usually up to 200ms) to be ready, check later. Values will be 0
```
