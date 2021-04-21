# std::unordered_map

## 直接源码

1. 从g++ 4.9.3挖出来的一段rehash的代码，看完懂的都懂.
```c++
template<typename _Key, typename _Value,
	   typename _Allocator, typename _ExtractKey, typename _Equal,
	   typename _H1, typename _H2, typename _Hash, typename _RehashPolicy,
	   bool __chc, bool __cit, bool __uk>
    void
    _Hashtable<_Key, _Value, _Allocator, _ExtractKey, _Equal,
	       _H1, _H2, _Hash, _RehashPolicy, __chc, __cit, __uk>::
    _M_rehash(size_type __n)
    {
      _Node** __new_array = _M_allocate_buckets(__n);
      __try
	{
	  for (size_type __i = 0; __i < _M_bucket_count; ++__i)
	    while (_Node* __p = _M_buckets[__i])
	      {
		std::size_t __new_index = this->_M_bucket_index(__p, __n);
		_M_buckets[__i] = __p->_M_next;
		__p->_M_next = __new_array[__new_index];
		__new_array[__new_index] = __p;
	      }
	  _M_deallocate_buckets(_M_buckets, _M_bucket_count);
	  _M_bucket_count = __n;
	  _M_buckets = __new_array;
	}
      __catch(...)
	{
	  // A failure here means that a hash function threw an exception.
	  // We can't restore the previous state without calling the hash
	  // function again, so the only sensible recovery is to delete
	  // everything.
	  _M_deallocate_nodes(__new_array, __n);
	  _M_deallocate_buckets(__new_array, __n);
	  _M_deallocate_nodes(_M_buckets, _M_bucket_count);
	  _M_element_count = 0;
	  __throw_exception_again;
	}
    }
```
2. reserve
```c++
void
      reserve(std::size_t __n)
      {
	__hashtable* __this = static_cast<__hashtable*>(this);
	__this->rehash(__builtin_ceil(__n / max_load_factor()));
      }
```