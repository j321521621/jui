#pragma once;

class Data
{
public:

	Data():m_size(0),m_data(0),m_datasize(0){}

	Data(const Data &ins):m_size(ins.m_size),m_data(0),m_datasize(ins.m_datasize)
	{
		m_data=new char[m_datasize];
		memcpy(m_data,ins.m_data,m_size);
	}

	Data& operator=(const Data &ins)
	{
		m_size=ins.m_size;
		m_datasize=ins.m_datasize;
		m_data=new char[m_datasize];
		memcpy(m_data,ins.m_data,m_size);
		return *this;
	}

	Data(char* data,DWORD size):m_size(0),m_data(0),m_datasize(0)
	{
		grow(size);
		memcpy(m_data,data,size);
	}


	~Data()
	{
		delete m_data;
	}

	char* getdata()
	{
		return m_data;
	}

	DWORD getsize()
	{
		return m_size;
	}

	void adddatablock(const Data& datablock)
	{
		grow(datablock.m_size);
		memcpy(m_data+m_size-datablock.m_size,datablock.m_data,datablock.m_size);
	}

	void addword(WORD val)
	{
		grow(2);
		*(PWORD)(m_data+m_size-2)=val;
	}

private:

	void grow(DWORD nsz)
	{
		if(m_size+nsz>m_datasize)
		{
			char* temp=m_data;
			m_datasize=2*(m_size+nsz);
			m_data=new char[m_datasize];
			memcpy(m_data,temp,m_size);
			delete temp;
		}

		m_size+=nsz;
	}

	DWORD m_size;
	char* m_data;
	DWORD m_datasize;
};