namespace safeareans
{

    enum SafeAreaStatus
    {
        STATUS_OK,
        STATUS_NOT_AVAILABLE,
        STATUS_NOT_READY_YET
    };
    
    struct Insets {
        float bottom, left, right, top;
    };

    struct Corners {
        float bottom_left, bottom_right, top_left, top_right;
    };

    void ResizeGameView(float* bg_color);
    SafeAreaStatus GetInsets(Insets* insets);
    SafeAreaStatus GetCornersRadius(Corners* corners);
    void SetBackgroundColor(float x, float y, float z, float w);
}
