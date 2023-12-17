#pragma once 

namespace STL {


	// ���������			// ��Ƿ���ֵ	// ��Ƿ���ָ��
	template<class Iterator, class Ref, class Ptr>	// ʹ������ģ�����������ٷ��� ����ȡ�� ʵ�ַ�ʽ
	struct ReverseIterator {
		typedef ReverseIterator<Iterator, Ref, Ptr> Self;		// ����������
		Iterator _current;										// ���һ����ǰ�㣨���ڸ�������������߼���
		// _current ����������ʼ����㣡
		// ������һ��λ�ã����������ǣ�_current => node->_prev

		ReverseIterator(Iterator iter)
			:_current(iter)
		{}

		// ���ؽ����ã�
		// �����������begin() => _head->_next;	/ end() => _head;
		// �����������rbegin() => _head; / rend() => _head->_next;
		// ���߸պöԳƣ��෴ָ��
		Ref operator * () {
			Iterator temp = _current;		// ��ʱ��ǵ�ǰ��
			--temp;							// ʵ�ַ����ƶ�
			return *(temp);
		}

		Ptr operator -> () {
			return &(operator*());
		}

		// ���� ǰ��++
		// �������������������������� ++ ���� ������-- ��������˫��������������ʵ����ǰ�ƶ�
		Self& operator ++ () {
			--_current;						// ��������������� --��ʵ��ָ��ǰ�ƣ����������߼���������
			return *this;					// ����ָ�����
		}
		// ���غ��� ++
		Self operator ++ (int) {
			Self temp(*this);
			--_current;
			return temp;
		}

		// ���غ��� --
		// �������������������������� -- ���� ������++ ��������˫��������������ʵ����ǰ�ƶ�
		Self& operator -- () {
			++_current;						// ��������������� ++��ʵ��ָ����ƣ����������߼���������
			return *this;
		}
		// ���غ��� --
		Self operator -- (int) {
			Self temp(*this);
			++_current;
			return temp;
		}

		bool operator != (const Self& iter) {
			return _current != iter._current;
		}
	};
}