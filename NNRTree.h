/**
 * File              : NNRTree.h
 * Author            : Pradeep Rajendran <pradeepunique1989@gmail.com>
 * Date              : 23.11.2018
 * Last Modified Date: 23.11.2018
 * Last Modified By  : Pradeep Rajendran <pradeepunique1989@gmail.com>
 */
#ifndef __NNRTREE_H__
#define __NNRTREE_H__

#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <vector>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
using namespace std;

#define DIM (7)

const size_t RANGE_MODE_TWO_NORM = 0;
const size_t RANGE_MODE_INF_NORM = 1;

// Define some types to make life easy
typedef bg::model::point<double, DIM, bg::cs::cartesian> point_t;
typedef std::pair<point_t, size_t> entry_t;

class NNRTree
{
private:
    bgi::rtree<entry_t, bgi::rstar<16> > rtree;
    std::map<size_t, entry_t> tree_entries;
    static point_t make_point(const double *const point_coords);
public:
    enum QueryType
    {
        RANGE_MODE_INF_NORM,
        RANGE_MODE_TWO_NORM
    };
    void insert_point(const double *const point_coords, const size_t id);
    void remove_point(const size_t id);
    std::vector<size_t> query_knn(const double *const point_coords_query, const size_t K_nearest_neighbors);
    std::vector<size_t> query_range(const double *const point_coords_query, const double radius, const QueryType range_mode);
};

#endif
