extern int i_last_checked;
class c_api_handler
{
public:
	std::string m_data;

	void get_latest_update( );

	std::vector<std::string> get_split_string( const std::string& stringToSplit, const std::string& regexPattern );

	int get_offset( const std::string & offset);

	int get_offsets_amount( ) {
		return m_offsets.size( );
	};
private:
	std::vector<int> m_offsets;
};
extern c_api_handler* g_api_handler( );