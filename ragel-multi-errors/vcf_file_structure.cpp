/* 
 * File:   vcf_file_structure.cpp
 * Author: Cristina Yenyxe Gonzalez Garcia <cyenyxe@ebi.ac.uk>
 * 
 * Created on 19 November 2014, 10:12
 */
#include "vcf_file_structure.h"

namespace opencb
{
  namespace vcf
  {
    
    VcfHeader::VcfHeader(string const & id, 
                         string const & plain_value)
    : id{id}, plain_value{plain_value}
    {
        
    }
        
    VcfHeader::VcfHeader(string const & id,
                         map<string, string> const & key_values)
    : id{id}, key_values{key_values}
    {
        
    }
   
    VcfRecord::VcfRecord(string const & chromosome, 
                         int const position, 
                         string const & id, 
                         string const & reference_allele, 
                         vector<string> const & alternate_alleles, 
                         float const quality, 
                         string const & filter, 
                         string const & info, 
                         string const & format, 
                         vector<string> const & samples) 
    : chromosome{chromosome}, 
        position{position}, 
        id{id}, 
        reference_allele{reference_allele}, 
        alternate_alleles{alternate_alleles}, 
        quality{quality}, 
        filters{filter}, 
        info{info}, 
        format{format}, 
        samples{samples}
    {
        if (quality < 0) {
            throw std::invalid_argument("Quality must be equal or greater than zero");
        }
    }

    bool VcfRecord::operator ==(VcfRecord const & other) {
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

    bool VcfRecord::operator!=(VcfRecord const & other) {
        return !(*this == other);
    }

  }
}
