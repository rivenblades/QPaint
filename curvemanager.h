#ifndef CURVEMANAGER_H
#define CURVEMANAGER_H

#include <iostream>
#include <cmath>
#include <vector>
#include <QPoint>
class CurveManager
{
public:
    CurveManager();
    float factorial(float n){
      return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
    }
    float binomial(int i, int n){return factorial(n)/(float)(factorial(i)* factorial(n-i));}
    float bernstein(float t, int i, int n){
        return binomial(i,n)*std::pow(t,i)*std::pow(1-t,n-i);
    }
    QPointF bezier(float t, std::vector<QPointF> points){
        int n = points.size() - 1;
        float x = 0;
        float y = 0;
        for(int i = 0; i < points.size(); i++){
            float bern = bernstein(t,i,n);
            x += points[i].x() * bern;
            y += points[i].y() * bern;
        }
        return QPointF(x,y);
    }
    std::vector<QPointF> bezier_curve_range(int n, std::vector<QPointF> points){
        std::vector<QPointF> tt;
        for(int i = 0; i < n; i++){
            float t = i / (float)(n-1);
            QPointF p = bezier(t,points);
            tt.push_back(p);
        }
        return tt;
    }

};

#endif // CURVEMANAGER_H
