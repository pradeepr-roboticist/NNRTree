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

#define DIM (10)

// const size_t RANGE_MODE_TWO_NORM = 0;
// const size_t RANGE_MODE_INF_NORM = 1;

#define SET_COORD(x) if (x < dim_limit_) bg::set<x>(out_pt, point_coords[x]); else bg::set<x>(out_pt, 0);

class NNRTree
{

private:
    size_t dim_limit_;
    typedef bg::model::point<double, DIM, bg::cs::cartesian> point_t;
    typedef std::pair<point_t, size_t> entry_t;

    bgi::rtree<entry_t, bgi::rstar<16> > rtree;
    std::map<size_t, entry_t> tree_entries;
    point_t make_point(const double *const point_coords)
    {
        point_t out_pt;
        SET_COORD(0);
        SET_COORD(1);
        SET_COORD(2);
        SET_COORD(3);
        SET_COORD(4);
        SET_COORD(5);
        SET_COORD(6);
        SET_COORD(7);
        SET_COORD(8);
        SET_COORD(9);    
        // bg::set<0>(out_pt, point_coords[0]);
        // bg::set<1>(out_pt, point_coords[1]);
        // bg::set<2>(out_pt, point_coords[2]);
        // bg::set<3>(out_pt, point_coords[3]);
        // bg::set<4>(out_pt, point_coords[4]);
        // bg::set<5>(out_pt, point_coords[5]);
        // bg::set<6>(out_pt, point_coords[6]);
        return out_pt;
    }

public:
    enum QueryType
    {
        RANGE_MODE_INF_NORM,
        RANGE_MODE_TWO_NORM
    };
    NNRTree(size_t const dim_limit): dim_limit_(dim_limit){};
    void insert_point(const double *const point_coords, const size_t id)
    {
        const entry_t entry = std::make_pair(make_point(point_coords), id);
        tree_entries[id] = entry;
        rtree.insert(entry);
    }

    void remove_point(const size_t id)
    {
        if (tree_entries.count(id) > 0)
        {
            rtree.remove(tree_entries[id]);
            tree_entries.erase(id);
        }
    }

    std::vector<size_t> query_knn(const double *const point_coords_query, const size_t K_nearest_neighbors)
    {
        std::vector<entry_t> result;
        rtree.query(bgi::nearest(make_point(point_coords_query), K_nearest_neighbors), std::back_inserter(result));

        std::vector<size_t> ids;
        std::transform(result.begin(), result.end(), std::back_inserter(ids), [](entry_t p) { return p.second; });
        return ids;
    }

    std::vector<size_t> query_range(const double *const point_coords_query, const double radius, const NNRTree::QueryType mode)
    {
        typedef bg::model::box<point_t> box;
        const point_t query_pt = make_point(point_coords_query);

        double lower_pt_arr[DIM];
        double upper_pt_arr[DIM];
        for (size_t k = 0; k < DIM; k++)
        {
            lower_pt_arr[k] = point_coords_query[k] - radius;
            upper_pt_arr[k] = point_coords_query[k] + radius;
        }
        const point_t lower_pt = make_point(lower_pt_arr);
        const point_t upper_pt = make_point(upper_pt_arr);
        const box query_box(lower_pt, upper_pt);

        std::vector<entry_t> result;

        if (NNRTree::QueryType::RANGE_MODE_INF_NORM == mode)
        {
            rtree.query(bgi::within(query_box), std::back_inserter(result));
        }
        else if (NNRTree::QueryType::RANGE_MODE_TWO_NORM == mode)
        {
            rtree.query(bgi::within(query_box) && 
                bgi::satisfies([&](entry_t const& v) {return bg::distance(v.first, query_pt) < radius;}),
                std::back_inserter(result));
        }

        std::vector<size_t> ids;
        std::transform(result.begin(), result.end(), std::back_inserter(ids), [](entry_t p) { return p.second; });
        return ids;
    }
};

#endif
