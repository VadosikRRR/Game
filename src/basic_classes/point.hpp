struct Point
{
private:
    int x;
    int y;

public:
    Point(int new_x, int new_y);
    int get_x() const ;
    int get_y() const;
    void change_x(int new_x);
    void change_y(int new_y);
};
