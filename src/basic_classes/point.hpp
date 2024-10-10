struct Point {
private:
    int x;
    int y;

public:
    Point(int new_x = 0, int new_y = 0);
    int get_x();
    int get_y();
    int change_x(int new_x);
    int change_y(int new_y);
};
