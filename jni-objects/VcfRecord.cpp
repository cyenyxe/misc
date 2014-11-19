/* 
 * File:   VcfRecord.cpp
 * Author: Cristina Yenyxe Gonzalez Garcia <cyenyxe@ebi.ac.uk>
 * 
 * Created on 19 November 2014, 10:12
 */

#include "VcfRecord.h"

VcfRecord::VcfRecord(const string & chromosome, const int position, const string & id, const string & reference_allele, 
        const vector<string> & alternate_alleles, const float quality, const string & filter, const string & info, 
        const string & format, const vector<string> & samples) :
            chromosome{chromosome}, position{position}, id{id}, reference_allele{reference_allele},
            alternate_alleles{alternate_alleles}, quality{quality}, filters{filter}, info{info}, format{format}, 
            samples{samples}
{
    if (quality < 0) {
        throw invalid_argument("Quality must be equal or greater than zero");
    }
}

bool VcfRecord::operator ==(const VcfRecord & other) {
    return chromosome == other.chromosome &&
            position == other.position &&
            id == other.id &&
            reference_allele == other.reference_allele &&
            alternate_alleles == other.alternate_alleles &&
            quality == other.quality &&
            filters == other.filters &&
            info == other.info &&
            format == other.format &&
            samples == other.samples;
}

bool VcfRecord::operator!=(const VcfRecord & other) {
    return !(*this == other);
}

