#pragma once
#include "CPlus/Global.h"
#include <string>
namespace CPlus
{
	namespace Node
	{
		struct ListNode {
			int val;  // �ڵ��ϴ洢��Ԫ��
			ListNode* next;  // ָ����һ���ڵ��ָ��
			ListNode(int x) : val(x), next(nullptr) {}  // �ڵ�Ĺ��캯��
			ListNode() : val(0), next(nullptr) {}
			ListNode(int x, ListNode* next) : val(x), next(next) {}
		};
		class NodeSolution
		{
		public:
			ListNode* RemoveElement(ListNode* LNode, int val)
			{
				// ɾ��ͷ���
				while (LNode != nullptr && LNode->val == val)
				{
					auto tmpNode = LNode;
					LNode = LNode->next;
					delete tmpNode;
				}
				// ɾ����ͷ�ڵ�
				auto curHead = LNode;
				// ���ǿ������Ҳ���β���ڵ�
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
				ListNode* pre = new ListNode();  //��ʼ��һ�� nullָ��Ľڵ�
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
				dummynode->next = head;  //����ͷ�ڵ�ָ�� ԭʼͷ�ڵ�
				ListNode* cur = dummynode;
				while (cur->next != nullptr && cur->next->next != nullptr) {
					temp = cur->next;  //������ʱ�ڵ�
					temp1 = cur->next->next->next;

					cur->next = temp->next;   //step1
					cur->next->next = temp;  //step2
					temp->next = temp1;    //step3
					cur = temp;            //׼����һ��
				}
				return dummynode->next;
			}
		private:

		};


	}
}