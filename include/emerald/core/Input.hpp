#pragma once

namespace emerald
{
    enum class InputType
    {
        // these are pre-set directions, distinct from keys, that are interchangeable between keyboard and controller
        UP,
        DOWN,
        LEFT,
        RIGHT,

        QUIT // general exit event for when the game ends
    };

    class Input
    {
    private:
        Input() = delete;
        ~Input() = delete;

        static bool up, down, left, right; // set directions on the arrow keys or d-pad [TODO]
        static bool quit;
        static int horizontal, vertical; // numerical value either 0 or 1 for multiplying movement; TODO: make this a float for joystick control

    public:
        static void update();

        static bool isDown(InputType type);
        static bool isQuit();

        static int getHorizontal();
        static int getVertical();
    };
}