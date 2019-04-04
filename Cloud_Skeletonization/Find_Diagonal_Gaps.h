#pragma once

#include "Life.h"
#include "IndexValue.h"

bool Increasing_Spans ( Life const& l1, Life const& l2 )
{
    return l1.span < l2.span;
}

bool Decreasing_Values ( IndexValue const& p1, IndexValue const& p2 )
{
    return p1.value > p2.value;
}

void Find_Diagonal_Gaps ( vector<Life>& persistence, int& index_above_gap, vector<IndexValue>& diag_gaps )
{
    size_t num_dots = persistence.size();
    
    sort( persistence.begin(), persistence.end(), Increasing_Spans );
    
    diag_gaps[0] = IndexValue( 0, persistence[0].span ); // Smallest gap.
    
    for (int i = 1; i < num_dots; ++i)
    {
        diag_gaps[i] = IndexValue( i, persistence[i].span - persistence[i - 1].span );
    }
    
    sort( diag_gaps.begin(), diag_gaps.end(), Decreasing_Values );
    
    index_above_gap = diag_gaps[0].index; // Index of dot above the 1st widest diagonal gap.
}
