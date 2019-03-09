#include "main.h"

int i_last_checked;
bool b_connected = false;

size_t writeFunction( void *ptr, size_t size, size_t nmemb, std::string* data ) {
	data->append( ( char* ) ptr, size * nmemb );
	return size * nmemb;
}

void c_api_handler::get_latest_update( )
{
	curl_global_init( CURL_GLOBAL_ALL );
	auto m_curl = curl_easy_init( );
	if ( m_curl )
	{

		curl_easy_setopt( m_curl, CURLOPT_URL, "https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.cs" );
		curl_easy_setopt( m_curl, CURLOPT_WRITEDATA, &m_data );
		curl_easy_setopt( m_curl, CURLOPT_WRITEFUNCTION, writeFunction );

		auto m_res = curl_easy_perform( m_curl );
		if ( m_res != CURLE_OK ) // checks for status code: 200
			fprintf( stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror( m_res ) );

		curl_easy_setopt( m_curl, CURLOPT_SSL_SESSIONID_CACHE, 0L );
		curl_easy_cleanup( m_curl );
	}
}

std::vector<std::string> c_api_handler::get_split_string( const std::string& stringToSplit, const std::string& regexPattern )
{
	std::vector<std::string> result;

	const std::regex rgx( regexPattern );
	std::sregex_token_iterator iter( stringToSplit.begin( ), stringToSplit.end( ), rgx, -1 );

	for ( std::sregex_token_iterator end; iter != end; ++iter )
	{
		result.push_back( iter->str( ) );
	}

	return result;
}

int c_api_handler::get_offset( const std::string& offset)
{
	if ( m_data.find( "netvars" ) != std::string::npos )
	{
		auto m_splitter = get_split_string( m_data, "\\n" );

		for ( int i = 9; i < m_splitter.size( ); i++ )
		{
			if ( m_splitter[ i ].find( offset ) != std::string::npos )
			{
				std::size_t m_size = offset.size( );
				std::string m_output = m_splitter[ i ].substr( 30 + m_size );
				m_output.replace( m_output.begin( ) + m_output.size( ) - 1, m_output.end( ), "" );
				int i_offset = strtol( m_output.c_str( ), NULL, 16 );

				m_offsets.push_back( i_offset );

				std::cout << offset << " -> " << "0x" << std::hex << std::uppercase << i_offset << std::endl;

				return i_offset;
			}
		}
	}
}

c_api_handler * g_api_handler( )
{
	static auto m_manager = std::make_unique< c_api_handler >( );
	return m_manager.get( );
}
