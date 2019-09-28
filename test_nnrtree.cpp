#include "NNRTree.h"

int main()
{
    NNRTree n;
    double pt0[] = {1, 2, 3, 4, 5, 6, 7};
    double pt1[] = {10, 2, 3, 4, 5, 6, 7};
    double pt2[] = {2, 2, 3, 4, 5, 6, 7};
    double pt3[] = {9, 2, 3, 4, 5, 6, 7};

    // Insert points and their corresponding IDs
    n.insert_point(pt0, 0);
    n.insert_point(pt1, 1);
    n.insert_point(pt2, 2);
    n.insert_point(pt3, 3);

    /***************************************************************************/
    // Query k-nearest neighbors
    {
        double pt_query[] = {8, 2, 3, 4, 5, 6, 7};
        // Now, query the 2 nearest neighbors that are close to the pt_query
        vector<size_t> IDs = n.query_knn(pt_query, 2);
        cout << "Closest IDs are: " << endl;
        for (int i = 0; i < IDs.size(); i++)
        {
            cout << "ID: " << IDs[i] << endl;
        }
    }
    /***************************************************************************/

    /***************************************************************************/
    // Query range
    {
        double pt_query[] = {8, 2, 3, 4, 5, 6, 7};
        // Now, query a range around pt_query
        vector<size_t> IDs = n.query_range(pt_query, 3, NNRTree::QueryType::RANGE_MODE_INF_NORM);
        cout << "IDs within range are: " << endl;
        for (int i = 0; i < IDs.size(); i++)
        {
            cout << "ID: " << IDs[i] << endl;
        }
    }
    /***************************************************************************/

    return 0;
}
