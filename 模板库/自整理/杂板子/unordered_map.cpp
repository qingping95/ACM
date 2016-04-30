
struct Node
{
	string str;
	int idx;
	bool operator==(const Node& o)const
	{
		return str==o.str && idx == o.idx;
	}
};
struct Node_hash
{
	size_t operator()(const Node& o)const
	{
		return hash<string>()(o.str) ^ (hash<int>()(o.idx) >> 1);
	}
};
unordered_map<Node,int,Node_hash> vis;

//我们需要重载==符号，以及另外在另一个结构体里面写hash函数，格式如上：
