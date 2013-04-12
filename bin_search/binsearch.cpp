#include <iostream>
#include <list>
#include <vector>

const int * BinSearch( const int * sortedArray, size_t size, int value )
{
	if ( size == 1 )
	{
		if ( sortedArray[0] == value )
		{
			return sortedArray;
		}
		else
		{
			return nullptr;
		}
	}
	else if ( size == 2 )
	{
		if ( sortedArray[0] == value )
		{
			return sortedArray;
		}
		else if ( sortedArray[1] == value )
		{
			return sortedArray + 1;
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		int mid = size / 2;
		if ( sortedArray[mid] == value )
		{
			return BinSearch( sortedArray, mid + 1, value );
		}
		else if ( sortedArray[mid] > value )
		{
			return BinSearch( sortedArray, mid, value );
		}
		else
		{
			mid++;
			return BinSearch( sortedArray + mid, size - mid, value );
		}
	}
}

class TestCase
{
public:
	TestCase( const int * sortedArray, size_t size, int value, const int * position ) :
		m_sortedArray( sortedArray ), 
		m_size( size ), 
		m_value( value ), 
		m_position( position )
	{

	}
	~TestCase() { };

	bool Test()
	{
		const int * found = BinSearch( m_sortedArray, m_size, m_value );
		return ( found == m_position );
	}

private:
	const int *	m_sortedArray;
	size_t		m_size;
	int			m_value;
	const int *	m_position;
};

int main( int argc, char **argv )
{
	int ar[] = { 1, 2, 3, 3, 4, 5, 7 };
	size_t size = sizeof( ar ) / sizeof( *ar );
	const int * found = BinSearch( ar, size, 6 );

	if ( found != nullptr )
	{
		std::cout << "value = " << *found <<
			" [" << found - ar << "]" << std::endl;
	}
	else
	{
		std::cout << "not found" << std::endl;
	}

	return 0;
}
