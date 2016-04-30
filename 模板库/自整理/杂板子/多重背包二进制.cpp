for(int i = 0; i < K; ++i){
	int num = ev[i].c;
	for(int k = 1; num; k <<= 1){
		int mul = min(k,num);
		for(int j = ev[i].a ; j >= mul * ev[i].h; --j)
			if(dp[j- ev[i].h*mul]) dp[j] = 1,ans = max(j,ans);
		num -= mul;
	}
}
for(int d = 0; d < w[i]; d++) {      // 对于所有余数 d [0, w[i])
		     // 窗口大小为 c[i]
    int sum = 0, st = 0, ed = -1;   //st,ed 单调队列的开始和结尾, sum 队列中是否有一个 true
    for(int v = d; v <= m; v+= w[i]) {   // 完全背包 model, 但步长是 w[i]
        if(ed - st == c[i]) {   // 窗口大小为0, 移除队首元素, 队首后移一位
            sum -= queue[st++];
	}
        queue[++ed] = dp[v];
        sum += dp[v];
        if(!dp[v] && sum)
            dp[v] = 1;
    }
}