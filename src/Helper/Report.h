#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Report{
private:
  vector<int> datas;
public:
  Report(vector<int> d)
  : datas {d}
  {}
  int max()
  {
    return *std::max_element(begin(datas),end(datas));
  }
  int min()
  {
    return *std::min_element(begin(datas),end(datas));
  }
  float means()
  {
    return accumulate(begin(datas),end(datas), 0.0f) / (float)datas.size();
  }
  float stddev()
  {
    float mean = means();
    return sqrt(accumulate(begin(datas),end(datas), 0.0f, [mean] (const int x, float acc) {
      return acc += pow((mean - x),2);
    }) / (float)datas.size());
  }
  void print(ostream& os,bool csv)
  {
    if(csv)
    {
      os << (int)means() << "," << (int)stddev() << "," << min() << "," << max() << endl;
    }
    else{
    os << "Mean : " << (int)means() << endl;
    os << "stddev : " << (int)stddev() << endl;
    os << "min : " << min() << endl;
    os << "max : " << max() << endl;
    os << endl;
  }
  }
};
