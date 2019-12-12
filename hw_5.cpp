
#include "Huffman.h"
#include <map>
#include <cstring>
#include <iostream>
#include <algorithm>


struct treeNode {
	// Структура, хранящая узлы дерева
    // Кодируемый символ
	byte symbol;
	// Частота
    int freq;
	// Левый потомок
    treeNode* Left;
	// Правй потомок
    treeNode* Right;
	treeNode(byte s, int f, treeNode* l, treeNode* r) : symbol(s), freq(f), Left(l), Right(r) {};
};


treeNode* join_nodes(treeNode* first, treeNode* second){
// Функция, объединяющая узлы в единый узел
	treeNode* out= new treeNode(0, first->freq+second->freq,first,second);
	return out;
}

bool comapre_treeNodes(const treeNode* first, const treeNode* second){
	// Компоратор узлов дерева
	return first->freq > second->freq;
}

vector<treeNode*> from_map_to_vector(map<byte, int> mp){
	// Функция делающая из map вектор(поскольку его удобно сортировать)
	vector<treeNode*> out;
	for(map<byte,int>::const_iterator it = mp.begin();
			it != mp.end(); ++it)
		{
			treeNode* new_node= new treeNode(it->first, it->second, nullptr, nullptr);
			out.push_back(new_node);
		}

		return out;
}


treeNode* build_tree(vector<treeNode*> in){
	// Функция, создающая дерево из вектора с частотами
	while(in.size()>1){
	std::sort(in.begin(),in.end(), comapre_treeNodes);
	treeNode* least1=in.back();
	in.pop_back();
	treeNode* least2=in.back();
	in.pop_back();
	in.push_back(join_nodes(least1, least2));
	}
	return in.front();
}

map <byte, int> create_dict(IInputStream& input, vector<byte>& mem){
	// Функция, считающая количество раз, которое встретился символ
	map <byte, int> mp;
	byte value;
	while (input.Read(value)) 
	{ 
		mem.push_back(value);
		if (mp.count(value) !=0){
			mp[value]+=1;
		} else {
			mp[value]=1;
		}
			}
	return mp;
}


void recursive_code(treeNode* node, byte& code,map <byte, byte>& out){
	// Шаг рекурсии для составления оптимального кода для символа
	 
	    if ((node->Right == nullptr) && (node->Left == nullptr)) {
			  out[node->symbol] = code;
			  code+=1;
        return;
    }
    recursive_code(node->Left, code,out);
    recursive_code(node->Right, code,out);
}

map <byte, byte> create_code(treeNode* root){
// Функция, создающая словарик символ -его код
	map <byte, byte> out;
	byte code=1;
	recursive_code(root, code, out);
	return out;
}

void out_map(map <byte, byte> coded,IOutputStream& output)
// Функция, записывающая в map соответствие кодов
{
	
	output.Write(coded.size());

	for(map<byte,byte>::const_iterator it = coded.begin();
			it != coded.end(); ++it)
		{
			
			output.Write(it->first);
			output.Write(it->second);
		}
		
}

map <byte, byte> in_map(IInputStream& input)
// функция получающая из map соответствие кодов
{
	byte dict_size;
	input.Read(dict_size);

	map <byte, byte> dict;
	byte value1;
	byte value2;
	for (int i=0; i<dict_size;++i)
	{
		input.Read(value1);
		input.Read(value2);
		dict[value2]=value1;
	};
	return dict;

}




static void copyStream(IInputStream& input, IOutputStream& output)
{
	byte value;
	while (input.Read(value)) 
	{ 
		output.Write(value); 
	} 
}



void Encode(IInputStream& original, IOutputStream& compressed) 
{
	vector<byte> mem;
	
		byte value;

	map<byte,int> mp=create_dict(original, mem);
	vector<treeNode*> vector_nodes=from_map_to_vector(mp);
	treeNode*  root=build_tree(vector_nodes);
	map <byte, byte> coded_dict=create_code(root);

		for(map<byte,byte>::const_iterator it = coded_dict.begin();
			it != coded_dict.end(); ++it)
		{
			// cout<<int(it->first)<<" "<<int(it->second)<<"\n";
		}
	// cout<<"end of first dict \n";
	out_map(coded_dict,compressed);

	for(int i=0; i<mem.size();i++)
	{

		// cout<<int(mem[i])<<" "<<int(coded_dict[mem[i]])<<"\n";
		compressed.Write(coded_dict[mem[i]]);
		
	}
		
}

void Decode(IInputStream& compressed, IOutputStream& original) 
{ 
	map <byte, byte> coded_dict=in_map(compressed);
// 	cout<<"new_dict \n";

// 		for(map<byte,byte>::const_iterator it = coded_dict.begin();
// 			it != coded_dict.end(); ++it)
// 		{
// 			cout<<(it->first)<<" "<<(it->second)<<"\n";
// 		}
// cout<<"start_out \n";
	byte value;
	byte value2;
	while (compressed.Read(value)) 
	{ 
		// true_unswer.Read(value2);
		// cout<<int(value)<<" "<<int(coded_dict[value])<<" "<<int(value2)<<"\n";
		original.Write(coded_dict[value]); 
	
	} 
}



int main()
{
	
// std::ifstream cin("Slovo o polku Igoreve.txt");
	// Получаем данные, которые нужно закодиров ать
	vector< vector<byte> > input;

// vector<byte> vec=vector<byte>((std::istreambuf_iterator<char>(file)),
//                  std::istreambuf_iterator<char>());


// input.push_back(vec);

	fillInputs(input);

	// Сжимаем данные
	vector< vector<byte> > compressed;
	compressed.resize(input.size());
	for (unsigned int i = 0; i < input.size(); i++) {
		CInputStream iStream(input[i]);
		CInputStream iStream2(input[i]);
		COutputStream oStream(compressed[i]);
		Encode(iStream, oStream);
	}

	// Распаковываем сжатые данные и проверяем, что они совпадают с оригиналом
	for (unsigned int i = 0; i < input.size(); i++) {
		vector<byte> output;
		CInputStream iStream(compressed[i]);
		CInputStream iStream2(input[i]);
		COutputStream oStream(output);
		Decode(iStream, oStream /*, iStream2*/);
		if (!isEqual(input[i], output)) {
			cout << -1;
			return 0;
		}
	}

	// Вычисляем степень сжатия
	cout << (100. * calculateSize(compressed) / calculateSize(input));
system("pause");
	return 0;
}


