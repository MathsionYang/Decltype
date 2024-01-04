#pragma once
#include "CPlus/Global.h"
#include <string>
namespace CPlus
{
	namespace Node
	{
		struct ListNode {
			int val;  // 节点上存储的元素
			ListNode* next;  // 指向下一个节点的指针
			ListNode(int x) : val(x), next(nullptr) {}  // 节点的构造函数
			ListNode() : val(0), next(nullptr) {}
			ListNode(int x, ListNode* next) : val(x), next(next) {}
		};
		class NodeSolution
		{
		public:
			ListNode* RemoveElement(ListNode* LNode, int val)
			{
				// 删除头结点
				while (LNode != nullptr && LNode->val == val)
				{
					auto tmpNode = LNode;
					LNode = LNode->next;
					delete tmpNode;
				}
				// 删除非头节点
				auto curHead = LNode;
				// 不是空链表且不是尾部节点
				while (curHead != nullptr && curHead->next != nullptr)
				{
					if (curHead->next->val == val)
					{
						auto tmpNode = curHead->next;
						curHead->next = curHead->next->next;
						delete tmpNode;
					}
					else
					{
						curHead = curHead->next;
					}
				}
				return LNode;
			}
			ListNode* ReverseListNode(ListNode* LNode)
			{
				ListNode* pre = new ListNode();  //初始化一个 null指针的节点
				pre = nullptr;
				ListNode* cur = new ListNode();
				cur = LNode;
				ListNode* tmp;
				while (cur != nullptr)
				{
					tmp = cur->next;
					cur->next = pre;
					pre = cur;
					cur = tmp;
				}
				return pre;
			}
			ListNode* swapPairs(ListNode* head) {
				ListNode* temp;
				ListNode* temp1;
				ListNode* dummynode = new ListNode(0);
				dummynode->next = head;  //虚拟头节点指向 原始头节点
				ListNode* cur = dummynode;
				while (cur->next != nullptr && cur->next->next != nullptr) {
					temp = cur->next;  //保存临时节点
					temp1 = cur->next->next->next;

					cur->next = temp->next;   //step1
					cur->next->next = temp;  //step2
					temp->next = temp1;    //step3
					cur = temp;            //准备下一轮
				}
				return dummynode->next;
			}
		private:

		};


	}
}