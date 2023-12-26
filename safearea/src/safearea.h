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

    void ResizeGameView(float* bg_color);
    SafeAreaStatus GetInsets(Insets* insets);
    void SetBackgroundColor(float x, float y, float z, float w);
}
