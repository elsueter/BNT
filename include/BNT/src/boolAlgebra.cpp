#include <BNT/booleanAlgebra.h>

using namespace BooleanAlgebra;

leaf::leaf(){
    label = "";
}

leaf::leaf(std::string in){
    if(in[in.length()-1] == '&'){
        label = in.substr(0, in.length()-1);
    }else if(in[in.length()-1] == '|'){
        label = in.substr(0, in.length()-1);
    }
    if(label[0] == '!'){
        type = 1;
    }else{
        type = 0;
        label = in;
    }
}

leaf::leaf(std::vector<std::string> in){
    label = in[0];
    if(label[label.length()-1] == '='){
        label.pop_back();
        label += in[1][in[1].length()-1];
    }
    if(label[label.length()-1] == '&'){
        type = 3;
    }else if(label[label.length()-1] == '|'){
        type = 4;
    }
    if(in.size() > 2){
        if(in[1][in[1].length()-1] == '&' || in[1][in[1].length()-1 == '|']){
            children.push_back(leaf(in[1]));
            children.push_back(leaf(std::vector<std::string>(in.begin()+2, in.end())));
        }
    }else{
        children.push_back(leaf(in[1]));
    }
}

std::string leaf::print(int depth){
    std::string out = "";
    if(depth > 0){
        out+="\n";
    }
    for(int i = 0; i < depth; i++){
        if(i < depth-1){
            out+="   ";
        }else{
            out+="-->";
        }
    }
    out += label;

    for(auto &it: children){
        out += it.print(depth+1);
    }

    return out;
}

boolTree::boolTree(std::string in){
    node.exp = in;
    std::cout<<"Node Expression: "<<node.exp<<std::endl;

    std::vector<std::string> parts = {""};
    int part = 0;
    for(int i = 0; i < in.length(); i++){
        if(in[i] != ' '){
            parts[part] += in[i];
        }
        if(in[i] == '|' || in[i] == '&' || in[i] == '='){
            parts.push_back("");
            part++;
        }
    }

    node.label = parts[0].substr(0, parts[0].length()-1);
    std::cout<<"Node Label: "<<node.label<<std::endl;

    tree = leaf(parts);

    std::cout<<tree.print(0)<<std::endl;
}