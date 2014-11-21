/* 
 * File:   vcf_file_structure.h
 * Author: Cristina Yenyxe Gonzalez Garcia <cyenyxe@ebi.ac.uk>
 *
 * Created on 19 November 2014, 10:12
 */

#ifndef OPENCB_VCF_VCFFILESTRUCTURE_H
#define	OPENCB_VCF_VCFFILESTRUCTURE_H

#include <string>
#include <map>
#include <vector>
#include <stdexcept>

namespace opencb
{
  namespace vcf
  {
    
    using std::string;
    using std::vector;
    using std::map;

    struct VcfHeader {
        string id;
        string plain_value;
        map<string, string> key_values;
        
        VcfHeader(string const & id,
                  string const & plain_value);
        
        VcfHeader(string const & id,
                  map<string, string> const & key_values);
    };
    
    struct VcfRecord {
        string chromosome;
        int position;
        string id;

        string reference_allele;
        vector<string> alternate_alleles;

        float quality;
        string filters;
        string info;
        string format;

        vector<string> samples;

        VcfRecord(string const & chromosome, 
                  int const position, 
                  string const & id, 
                  string const & reference_allele, 
                  vector<string> const & alternate_alleles, 
                  float const quality, 
                  string const & filter, 
                  string const & info, 
                  string const & format, 
                  vector<string> const & samples);

        bool operator==(VcfRecord const &);

        bool operator!=(VcfRecord const &);
    };

  }
}

#endif	/* VCFRECORD_H */

