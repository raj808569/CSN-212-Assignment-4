
#include <bits/stdc++.h>
using namespace std;
 
struct point
{
    int x, y;
};

int orientation(point p, point q, point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

int pointLocation(point A, point B, point P)
    {
        int cp1 = (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
        if (cp1 > 0)
            return 1;
        else if (cp1 == 0)
            return 0;
        else
            return -1;
    }
    
 int distance(Point A, Point B, Point C)
    {
        int ABx = B.x - A.x;
        int ABy = B.y - A.y;
        int num = ABx * (A.y - C.y) - ABy * (A.x - C.x);
        if (num < 0)
            num = -num;
        return num;
    }
    
  void hullSet(point A, point B, vector<point>set,vector<point>hull)
  {
  	 it=find(hull.begin(),hull.end(),B);
  	 int insertPosition = *it;
  	 
  	if (set.size() == 0)
            return;
            
    if (set.size() == 1)
        {
            point p = set[0];
            set.erase(set.begin()+0);
            hull.insert(it, p);
            return;
        }
        
    int dist = INT_MIN;
        int furthestPoint = -1;
        for (int i = 0; i <set.size(); i++)
        {
            point p = set[i];
            int distance = distance(A, B, p);
            if (distance > dist)
            {
                dist = distance;
                furthestPoint = i;
            }
        }
    
     Point P = set[furthestPoint];
        set.erase(set.begin()+furthestPoint-1);
        hull.insert(it, P);
        
    // Determine who's to the left of AP
        vector<point>leftSetAP;
        for (int i = 0;i < set.size(); i++)
        {
            point M = set[i];
            if (pointLocation(A, P, M) == 1)
            {
                leftSetAP.push_back(M);
            }
        }
 
        // Determine who's to the left of PB
        vector<point>leftSetPB;
        for (int i = 0; i < set.size(); i++)
        {
            point M = set[i];
            if (pointLocation(P, B, M) == 1)
            {
                leftSetPB.push_back(M);
            }
        }
        hullSet(A, P, leftSetAP, hull);
        hullSet(P, B, leftSetPB, hull);
    
  }

void convexHull(point sample[], int n)
{
	
	if(n<3) return;
	// Initialize Result
    vector<point> hull;
    vector<point> Lefthull;
    vector<point> Righthull;
	
	 int minPoint = -1, maxPoint = -1;
        int minX = INT_MAX;
        int maxX = INT_MIN;
        for (int i=0;i<n; i++)
        {
            if (sample[i].x < minX)
            {
                minX = sample[i].x;
                minPoint = i;
            }
            if (sample[i].x > maxX)
            {
                maxX =sample[i].x;
                maxPoint = i;
            }
        }
        
         hull.push_back(sample[minPoint]);
         hull.push_back(sample[maxPoint]);
         
        Point A = sample[minPoint];
        Point B = sample[maxPoint];
         
          for(int i=0;i<n; i++)
        {
            point p = sample[i];
            if (pointLocation(A, B, p) == -1)
               Lefthull.push_back(p);
            else if (pointLocation(A, B, p) == 1)
                 Righthull.push_back(p);
        }
         
        hullSet(A, B, Righthull, hull);
        hullSet(B, A, Lefthull, hull); 
        
        
    // Print Result
    for (int i = 0; i < hull.size(); i++)
        cout << "(" << hull[i].x << ", "
              << hull[i].y << ")\n";   
              
}

int main() {
	 point sample[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1},
                      {3, 0}, {0, 0}, {3, 3}};
    int n = sizeof(sample)/sizeof(sample[0]);
    convexHull(sample, n);
	return 0;
}
