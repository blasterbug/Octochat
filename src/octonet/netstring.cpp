#include "octonet/netstring.hpp"

std::size_t netstring_decode(const char * __netstring, std::size_t __max_len, const char ** __string)
{
	int _err;
    char _buffer[LEN_BUFFER_SIZE];
    std::size_t _cpy_count;
    char * _chr_ret;
    std::size_t _len;
    char * _end_ptr;
    std::size_t _buffer_len;
    unsigned short _i;
    
    _err = 0;
    _len = 0;
	*__string = __netstring;
    if((__netstring == NULL) || (__max_len < 3))
    {
		_err = 1;
	}
	else
	{
		_cpy_count = (__max_len < LEN_BUFFER_SIZE) ? __max_len : LEN_BUFFER_SIZE;
		std::memcpy(_buffer, __netstring, _cpy_count*sizeof(char));
		_chr_ret = static_cast<char*>(std::memchr(_buffer, ':', _cpy_count*sizeof(char)));
		if(_chr_ret == NULL)
		{
			_err = 2;
		}
		else
		{
			*_chr_ret = '\0';
			for(_i=0; _i<_cpy_count; _i++)
			{
				if((std::isdigit(_buffer[_i]) == 0) || (_buffer[_i] == '\0'))
				{
					break;
				}
			}
			if((_buffer+_i) != _chr_ret)
			{
				_err = 3;
			}
			else
			{
				errno = 0;
				_len = std::strtoul(_buffer, &_end_ptr, 10);
				if((errno == ERANGE && (_len == ULONG_MAX || _len == 0)) || (errno != 0 && _len == 0))
				{
					_err = 4;
				}
				else
				{
					if(_end_ptr == _buffer)
					{
						_err = 5;
					}
					else
					{
						_buffer_len = std::strlen(_buffer);
						if((_buffer_len+1+_len+1) > __max_len)
						{
							_err = 6;
						}
						else
						{
							if(__netstring[_buffer_len+1+_len] != ',')
							{
								_err = 7;
							}
							else
							{
								*__string = __netstring + (_buffer_len + 1);
							}
						}
					}
				}
			}
		}
	}
	errno = _err;
    return _len;
}
