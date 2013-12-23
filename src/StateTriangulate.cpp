#include "StateTriangulate.hpp"
#include "Triangle.hpp"
#include "Point.hpp"

bool IsCounterClockwise(CGUL::Vector< CGUL::Vector2 > inPoints)
{
    using namespace CGUL;

    int count = 0, j = 0, k = 0;

    // Don't bother if there's less than 3 points, just assume its counter clockwise
    if (inPoints.size() < 3)
    {
        return true;
    }

    for (int i = 0; i < inPoints.size(); i++)
    {
        // Get the next two points
        j = (i + 1) % inPoints.size();
        k = (i + 2) % inPoints.size();

        // Get the direction of each points
        Vector2 valueA = inPoints[j] - inPoints[i];
        Vector2 valueB = inPoints[k] - inPoints[j];

        // Check if the cross product between the two directions is positive,
        // if so this point is clockwise
        count = (valueA.x * valueB.y - valueA.y * valueB.x < 0) ? (count + 1) : (count - 1);
    }

    // Determine clockwise-ness by which one was more common.
    // More CW points is CW, more CCW points is CCW.
    // A partial guess but it works for pracitcal means.
    return (count < 0);
}

bool Triangulate(CGUL::Vector< CGUL::Vector2 > inPoints, CGUL::Vector< Triangle >* triangles)
{
    using namespace CGUL;

    if (inPoints.size() < 3)
    {
        return false;
    }

    Vector< Vector2 > points;
    for (Vector< Vector2 >::iterator itr = inPoints.begin(); itr < inPoints.end(); itr++)
    {
        points.push_back(*itr);
    }

    bool finished = false;
    Vector2 point;

    // The three points of our potential ear
    Vector2 point1;
    Vector2 point2;
    Vector2 point3;

    while (!finished)
    {
        int i = 0;
        bool found = false;

        while (!found && (i < points.size()))
        {
            // Set the point to our current point
            point1 = points[i];

            // Begin checking if we found an ear
            bool isEar = true;

            // Find the previous point
            if (i == 0)
            {
                point2 = points[points.size() - 1];
            }
            else
            {
                point2 = points[i - 1];
            }

            // Find the next point
            if (i == points.size() - 1)
            {
                point3 = points[0];
            }
            else
            {
                point3 = points[i + 1];
            }

            // Find the area of the ear
            double area = 0;
            area += point2.x * point1.y;
            area -= (point2.y * point1.x);
            area += point1.x * point3.y;
            area -= (point1.y * point3.x);
            area += point3.x * point2.y;
            area -= (point3.y * point2.x);
            area = area / 2;

            // Is the ear convex?
            if (area < 0)
            {
                for (int j = 0; j < points.size() - 1; j++)
                {
                    // check if good ear
                    Vector2 pointCheck = points[j];
                    if (!(pointCheck == point1 || pointCheck == point2 || pointCheck == point3))
                    {
                        if (Triangle(Vector2(0, 0), point2, point1, point3, 0).CollidingPoint(Point(pointCheck)))
                        {
                            isEar = false;
                        }
                    }
                }
            }
            else // not a good ear
            {
                isEar = false;
            }

            // ear
            if (isEar)
            {
                found = true;
            }
            else // not ear
            {
                i++;
            }
        }

        // triangulation failed
        if (found == false)
        {
            return false;
        }

        for (int j = 0; j < points.size(); j++)
        {
            if (i == j)
            {
                // found an ear
                triangles->push_back(Triangle(Vector2(0, 0), point2, point1, point3, 0));

                // remove the point from the list
                points.erase(points.begin() + j);
            }
        }

        if (points.size() == 3)
        {
            triangles->push_back(Triangle(Vector2(0, 0), points[0], points[1], points[2], 0));
            finished = true;
        }
    }

    return true;
}

StateTriangulate::StateTriangulate()
{
}

StateTriangulate::~StateTriangulate()
{
}

void StateTriangulate::Enter()
{
    render->SetClearColor(CGUL::Colors::darkBlue);
    window->SetTitle(U8("Triangulate - Physics Stuff by Joshua \"jalb\" Brookover"));
}

void StateTriangulate::Update(CGUL::Float32 deltaTime)
{
    using namespace CGUL;
    Vector2 mousePos = stateMachine->GetMousePosition();

    if (stateMachine->IsButtonPressed(0))
    {
        points.push_back(mousePos);

        if (IsCounterClockwise(points))
        {
            std::cout << "CCW!!" << std::endl;
        }
        else
        {
            std::cout << "CW!!" << std::endl;
        }
    }

    if (stateMachine->IsKeyPressed('R'))
    {
        points.clear();
    }

    for (Vector< Vector2 >::iterator itr = points.begin(); itr != points.end(); itr++)
    {
        render->Circle(*itr, 4, Colors::green);
        if (itr + 1 == points.end())
        {
            render->Line(*itr, *(points.begin()), Colors::green);
        }
        else
        {
            render->Line(*itr, *(itr + 1), Colors::green);
        }
    }

    Vector< Triangle > triangles;
    Triangulate(points, &triangles);

    if (!stateMachine->IsKeyDown('H'))
    {
        for (Vector< Triangle >::iterator itr = triangles.begin(); itr != triangles.end(); itr++)
        {
            Triangle& triangle = *itr;
            render->Line(triangle.pointA, triangle.pointB, Colors::red);
            render->Line(triangle.pointB, triangle.pointC, Colors::red);
            render->Line(triangle.pointC, triangle.pointA, Colors::red);
        }
    }

    render->Circle(mousePos, 2, Colors::red);
}

void StateTriangulate::Exit()
{
}
