struct Point {
private:
  int x_;
  int y_;

public:
  Point(int new_x = 0, int new_y = 0);
  int getX() const;
  int getY() const;
  void changeX(int new_x);
  void changeX(int new_y);
};
