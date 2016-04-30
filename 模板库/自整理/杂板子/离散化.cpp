cnt = 0;
int len = 1;
for(int i=1;i<=n;i++)
{
	int a, b;
	scanf("%d%d", &a, &b);
//            read(a);read(b);
	if(a == 0){
		q[i] = node(a, b, b+len);
		mp[cnt++] = b, mp[cnt++] = b+len;
		idx[len] = i;
		len++;
	}else{
		q[i] = node(a, q[idx[b]].l, q[idx[b]].r);
	}
}
sort(mp, mp+cnt);
cnt = unique(mp, mp+cnt) - mp;
for(int i=1;i<=n;i++)
{
	q[i].l = lower_bound(mp, mp+cnt, q[i].l) - mp + 1;
	q[i].r = lower_bound(mp, mp+cnt, q[i].r) - mp + 1;
}