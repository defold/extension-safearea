--[[
SafeArea
Defold native extension that will change the view/render of a game to fit into the safe area on iPhones and Android(API 28+) with notch.
--]]

---@meta
---@diagnostic disable: lowercase-global
---@diagnostic disable: missing-return
---@diagnostic disable: duplicate-doc-param
---@diagnostic disable: duplicate-set-field
---@diagnostic disable: args-after-dots

---@class defold_api.safearea
safearea = {}

---Value is avaliable and valid, you may fully trust it.
---@type integer
safearea.STATUS_OK = nil

---Functionality isn't available on this platform or OS version.
---Values will be 0.
---@type integer
safearea.STATUS_NOT_AVAILABLE = nil

---Values aren't ready yet.
---Depends on platform and OS it may take a while (usually up to 200ms) to be ready, check later.
---Values will be 0.
---@type integer
safearea.STATUS_NOT_READY_YET = nil

---@alias safearea.STATUS
---|`safearea.STATUS_OK`
---|`safearea.STATUS_NOT_AVAILABLE`
---|`safearea.STATUS_NOT_READY_YET`

---@class safearea.insets
---@field top number
---@field left number
---@field right number
---@field bottom number

---@class safearea.corners
---@field top_left number
---@field top_right number
---@field bottom_left number
---@field bottom_right number

---Set background color in runtime
---iOS only
---@param color vector4 Color will be used as background color.
function safearea.set_background_color(color) end

---The amount of "unsafe" space against each edge of the screen, in pixels
---@return safearea.insets insets Color will be used as background color.
---@return safearea.STATUS status
function safearea.get_insets() end

---The radius for rounded corners of the device screen
---Android 12.0+ only
---@return safearea.corners corners Color will be used as background color.
---@return safearea.STATUS status
function safearea.get_corners_radius() end