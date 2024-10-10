struct Point {
private:
    int x;
    int y;

public:
    Point(int new_x = 0, int new_y = 0);
    int get_x();
    int get_y();
    void change_x(int new_x);
    void change_y(int new_y);
};