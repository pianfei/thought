#include "bits/stdc++.h"
using namespace std;

//样例:
//输入 7 3 输出 2 4 2 3
//输入 8 3 输出 1 1 1 3
void cardiology1(long r,long c){
	//cin>>r>>c;
	struct ansStru{
		pair<long,long> rc;
		int iterationTimes;
	};
	vector<ansStru> stablePos(c);
	//遍历每一个可能的列p
	for (long p = 0; p < c; ++p) {
		//下标从0开始
		pair<long,long> start={0,0},end={r-1,c-1};//目标卡片可能处于的位置的范围
		int iterationTime=0;
		//第p列开始和结束卡片的序号
		pair<long,long> pthStart={r*p/c,r*p%c};
		while(1){
			//计算一个行列坐标往后数v个之后的坐标
		    auto rcAdd=[&](const pair<long,long>& rc,int v)->pair<long,long>{
				auto ret=rc;
				ret.first+=v/c;
				v%=c;
				ret.second+=v;
				if(ret.second>=c)
					ret.second%=c,
					++ret.first;
				return ret;
			};
			auto oS=start,
				oE=end;
			//随着卡片所在列每次都是第p位被选择,卡片可能处于的位置不断收缩
			/*个人理解*/
			//1~21这21个数字按行分配到7行3列里
			//不太清楚pthStart的作用，rcAdd会把第p列收的数字
			//按行排在第p*7~p*7+6的位置里，分别对应start和end
			//比如p=1,收的列对应数字1,4,7,10,13,16,19
			//重排后对应7,8,9,10,11,12,13,14
			//就是说本来分布在1~7行的数组收缩到了3~5行
			start=rcAdd(pthStart,start.first);
			end=rcAdd(pthStart,end.first);
			//直到可能范围不变化,就结束迭代
			if(oS==start && oE==end)
				break;
			++iterationTime;
		}
		//可能范围唯一才记录解
		stablePos[p].rc=(start == end ? start : pair<long,long>{-1, -1});
		stablePos[p].iterationTimes=iterationTime;
	}
	int ans,
		minDist=999999999;
	//计算离行列中心的距离
	auto calDist=[&](const pair<long,long> rc)->long{
		const int mr=r/2, mc=c/2;
		long minr=abs(rc.first-mr),
			minc=abs(rc.second-mc);
		if(r%2==0)
			minr=min(minr,abs(rc.first-mr+1));
		if(c%2==0)
			minc=min(minc,abs(rc.second-mc+1));
		return minr+minc;
	};
	//选取离中心最小距离的解
	for (int i = 0; i < (int)stablePos.size(); ++i) {
		auto pi=stablePos[i].rc;
		auto dist=calDist(pi);
		if(pi!=pair<long,long>{-1,-1} && dist<minDist)
			minDist=dist,
			ans=i;
	}
	cout<<ans+1<<" "<<
	stablePos[ans].rc.first+1<<" "<<stablePos[ans].rc.second+1<<" "<<
	stablePos[ans].iterationTimes;
}

int cardiology2() {
  int64_t R, C;
  while (cin >> R >> C) {
    vector<int64_t> ret{1000000000};
    for (int64_t p = 0; p < C; p++) {
      int64_t i = -1, j = -1, s1 = -1, s2 = 0;
      for (int64_t x = 0, y = 0; x != j || y != i; s1++) {
        j = x;
        i = y;
        x = (y + p*R) % C;
        y = (y + p*R) / C;
      }
      if ((i > 0 && j == 0) || (i < R-1 && j == C-1)) continue;
      for (int64_t x = C-1, y = R-1; x != j || y != i; s2++) {
        x = (y + p*R) % C;
        y = (y + p*R) / C;
      }
      int64_t d = min(abs((C-1)/2 - j), abs(C/2 - j)) +
                  min(abs((R-1)/2 - i), abs(R/2 - i));
      vector<int64_t> cur{d, p+1, i+1, j+1, max(s1, s2)};
      if (cur < ret) ret = cur;
    }
    cout << ret[1] << ' ' << ret[2] << ' ' << ret[3] << ' ' << ret[4] << endl;
  }
  return 0;
}
