for(int i = 0; i < K; ++i){
	int num = ev[i].c;
	for(int k = 1; num; k <<= 1){
		int mul = min(k,num);
		for(int j = ev[i].a ; j >= mul * ev[i].h; --j)
			if(dp[j- ev[i].h*mul]) dp[j] = 1,ans = max(j,ans);
		num -= mul;
	}
}
for(int d = 0; d < w[i]; d++) {      // ������������ d [0, w[i])
		     // ���ڴ�СΪ c[i]
    int sum = 0, st = 0, ed = -1;   //st,ed �������еĿ�ʼ�ͽ�β, sum �������Ƿ���һ�� true
    for(int v = d; v <= m; v+= w[i]) {   // ��ȫ���� model, �������� w[i]
        if(ed - st == c[i]) {   // ���ڴ�СΪ0, �Ƴ�����Ԫ��, ���׺���һλ
            sum -= queue[st++];
	}
        queue[++ed] = dp[v];
        sum += dp[v];
        if(!dp[v] && sum)
            dp[v] = 1;
    }
}