#ifndef windy_key
#define windy_key


namespace windy {

	class key {
	public:
		enum class status {
			down,
			up
		};

		enum class codes {
			up, 
			down, 
			left, 
			right,
			a, 
			b, 
			c, 
			start
		};

		key() {
			this->_status = status::up;
			this->_released = false;
			this->_pressed = false;
		}

		status _status;
		bool _released;
		bool _pressed;
	};

}


#endif