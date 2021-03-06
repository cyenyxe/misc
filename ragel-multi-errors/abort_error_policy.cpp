#include "vcf_validator.hpp"

namespace
{
  using namespace opencb::vcf;

  void throw_syntax_error(ParsingState const &)
  {
    throw ParsingError("invalid VCF syntax");
  }
  
  void throw_syntax_error(std::string const & msg)
  {
    throw ParsingError(msg);
  }
}

namespace opencb
{
  namespace vcf
  {

    void AbortErrorPolicy::handle_fileformat_section_error(ParsingState const & state)
    {
        std::stringstream msg;
        msg << "Line " << state.n_lines << ": Error in fileformat section";
        throw_syntax_error(msg.str());
    }

    void AbortErrorPolicy::handle_meta_section_error(ParsingState const & state)
    {
        std::stringstream msg;
        msg << "Line " << state.n_lines << ": Error in meta section";
        throw_syntax_error(msg.str());
    }

    void AbortErrorPolicy::handle_header_section_error(ParsingState const & state)
    {
        std::stringstream msg;
        msg << "Line " << state.n_lines << ": Error in header section";
        throw_syntax_error(msg.str());
    }

    void AbortErrorPolicy::handle_body_section_error(ParsingState const & state)
    {
        std::stringstream msg;
        msg << "Line " << state.n_lines << ": Error in body section";
        throw_syntax_error(msg.str());
    }

  }
}
