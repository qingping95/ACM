
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

//������Ҫ����==���ţ��Լ���������һ���ṹ������дhash��������ʽ���ϣ�
