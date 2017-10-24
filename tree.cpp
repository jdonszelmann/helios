struct treeitem{
    string name;
    int linennum;
    int type;
};

struct Current{
    void * current;
};

class objectTree{
    public:
        // struct * content;
        treeitem * content;
        vector<objectTree *> childs;
        objectTree * parent;
        Current * current;

        objectTree(objectTree * parent, Current * current, treeitem * content){
            this->content = content;
            this->parent = parent;
            this->current = current;
        }

        objectTree(treeitem * content){
            this->content = content;
            this->parent = this;
            Current * current = new Current();
            current->current = this;
            this->current = current;
        }

        objectTree * appendChild(treeitem * content, bool select = false){
            objectTree * temp = static_cast<objectTree *>(this->current->current);
            objectTree * item = new objectTree(temp,this->current,content);
            if(select){
                item->current->current = item;
            }
            temp->childs.push_back(item);
            return item;
        }

        void moveback(){
            this->current->current=static_cast<objectTree *>(this->current->current)->parent;
        }

        void printall(){
            if(this->parent = this){
                this->print(0);
                return;
            }else{
                parent->print();
                return;
            }
        }

        objectTree * top(){
            if(this->parent = this){
                return this;
            }else{
                return this->parent->top();
            }
        }

        void settop(){
            if(this->parent = this){
                this->current->current = this;
                return;
            }else{
                this->parent->top();
                return;
            }
        }

        void select(int item){
            if (item < static_cast<objectTree *>(this->current->current)->childs.size()){
                this->current->current = static_cast<objectTree *>(this->current->current)->childs[item];
            }
        }

        void print(int indent = 0){
            for (int i = 0; i < indent-1; ++i)
            {
                cout<<char(179);
            }
            if (indent>0){
                cout<<char(195);
            }
            if (this->childs.size()==0){
                cout<<char(196);
            }else{
                cout<<char(194);
            }

            if (this->current->current == this){
                cout<<this->content->name<<" <--CURRENT"<<endl;
            }else{
                cout<<this->content->name<<endl;
            }

            for (int i = 0; i < this->childs.size(); ++i)
            {
                this->childs[i]->print(indent + 1);
            }
        }
};