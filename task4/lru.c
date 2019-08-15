/*
实现一个LRU缓存淘汰算法

LRU（Least recently used，最近最少使用）缓存算法根据数据最近被访问的情况来进行淘汰数据，其核心思想是“如果数据最近被访问过，那么将来被访问的几率也更高”。

最常见的实现是使用一个链表保存缓存数据，详细算法实现如下：
1. 新数据插入到链表头部；

2. 每当缓存命中（即缓存数据被访问），则将数据移到链表头部；

3. 当链表满的时候，将链表尾部的数据丢弃。

Some good examples
https://www.geeksforgeeks.org/lru-cache-implementation/
https://github.com/Stand1210/c-LRU-
 */
