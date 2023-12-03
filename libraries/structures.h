#include <iostream>
#include "useful_functions.h"





namespace data_structures {

	namespace {


		template <typename data_> class node_root {

			protected:
				data_ this_data;
			
			public:

				node_root(){}

				node_root(data_ new_data) : this_data(new_data){
				}

				void set_data(data_ d) {
					this->this_data = d;
				}

				data_ get_data() const {
					return this->this_data;
				}

				data_ &get_data_ref() {
					return this->this_data;
				}

		};


		template <typename data_, typename indx_ = signed long> class numbered_node : public node_root<data_> {


			private:
				indx_ index;



			protected:

				void set_index(indx_ index) {
					this->index = index;
				}


				indx_ get_index() const {
					return this->index;
				}

			public:

				numbered_node() {
				}

				numbered_node(data_ new_data, indx_ index = -1) : node_root<data_>(new_data) {
					this->index = index;
				}

		};


		template <typename data_> class linear_node : public node_root<data_> {
			
			protected:
				linear_node<data_>* next_node;
				linear_node<data_>* previous_node;

			public:

				linear_node() {
					this->next_node = nullptr;
				}

				linear_node(data_ new_data, linear_node<data_>* next = nullptr, linear_node<data_>* previous = nullptr) {
					this->this_data = new_data;
					this->next_node = next;
					this->previous_node = previous;
				}

				void set_next(linear_node<data_>* next) {
					this->next_node = next;
				}

				linear_node<data_>* get_next() const {
					return this->next_node;
				}

				void set_previous(linear_node<data_>* previous) {
					this->previous_node = previous;
				}

				linear_node<data_>* get_previous() const {
					return this->previous_node;
				}

		};


		template <typename data_> class bst_node : public numbered_node <data_, signed long> {

			private:
				bst_node<data_>* left_child, *right_child, *parent;

			public:

				bst_node() {
					this->left_child = this->right_child = parent = nullptr;
					this->set_index(-1);
				}

				bst_node(data_ new_data, signed long height = -1) {
					this->this_data = new_data;
					this->set_index(height);
					this->left_child = this->right_child = parent = nullptr;
				}

				void set_left_child(bst_node<data_>* left) {
					this->left_child = left;
				}

				void set_right_child(bst_node<data_>* right) {
					this->right_child = right;
				}

				void set_parent(bst_node<data_>* mother) {
					this->parent = mother;
				}

				bst_node<data_>* get_left_child() {
					return this->left_child;
				}

				bst_node<data_>* get_right_child() {
					return this->right_child;
				}

				bst_node<data_>* get_parent() {
					return this->parent;
				}

				void set_height(signed long height) {
					this->set_index(height);
				}

				void set_h(signed long height) {
					this->index = height;
				}

				signed long get_height() const {
					return this->get_index();
				}

				signed long get_h() const {
					return this->index;
				}

		};

	}


	template <typename data_> class linear_linked_list {


		private:
			linear_node<data_> *front, *rear, *frame;
			unsigned long size, frame_index;

			void node_shifter(linear_node<data_>* this_node, unsigned long node_index, signed long by) {

				signed long start_index = (signed long) node_index;
				while ((by != 0) && (this_node != nullptr) && (node_index != by)) {
					if (by > 0) {
						this_node = this_node->get_next();
						node_index = node_index + 1;
					}
					else {
						this_node = this_node->get_previous();
						node_index = node_index - 1;
					}
				}
			}

			void frame_shifter(signed long by) {
				while ((by != 0) && (this->frame != nullptr)) {
					this->frame = (by > 0) ? this->frame->get_next() : this->frame->get_previous();
					this->frame_index = (by > 0) ? this->frame_index + 1 : this->frame_index - 1;
					by = (by > 0) ? by - 1 : by + 1;
				}
			}


		public:

			linear_linked_list() {
				this->front = this->rear = this->frame = nullptr;
				this->size = 0;
			}


			linear_linked_list(data_ new_data) {
				this->front = this->rear = this->frame = new linear_node<data_>(new_data);
				this->size = 1;
			}


			// Copy Constructor

			linear_linked_list(linear_linked_list<data_>& other_list) {
				if (this == &other_list) {
					return;
				}
				this->size = 0;
				unsigned long index;
				for (index = 0; index < other_list.length(); index = index + 1) {
					this->push(other_list.peek(index));
				}
			}


			~linear_linked_list() {
				this->reset();
			}

			// Operator Overloading.

			// Assignment Operators
			// TODO CREATE ASSIGNMENT OPERATORS

			// Comparison operators

			bool operator==(linear_linked_list<data_>& other) {
				fprintf(stderr, "== operator not yet implemented\n");
				exit(EXIT_FAILURE);
				if (this == *other) {
					return true;
				}
				unsigned long other_index = 0;

				for (this->frame = this->front, this->frame_index = 0; this->frame != nullptr; this->frame = this->frame->get_next(), this->frame_index = this->frame_index + 1) {
					if (this->frame->get_data() != other[this->frame_index]) {
						return false;
					}
				}
				return true;
			}




			bool operator!=(linear_linked_list<data_>& other) {
				fprintf(stderr, "!= operator not yet implemented\n");
				exit(EXIT_FAILURE);
				if (this != *other) {
					return true;
				}
				unsigned long other_index = 0;

				for (this->frame = this->front, this->frame_index = 0; this->frame != nullptr; this->frame = this->frame->get_next(), this->frame_index = this->frame_index + 1) {
					if (this->frame->get_data() == other[this->frame_index]) {
						return false;
					}
				}
				return true;
			}




			bool operator<=(linear_linked_list<data_>& other) {
				fprintf(stderr, "<= operator not yet implemented\n");
				exit(EXIT_FAILURE);
			}



			bool operator>=(linear_linked_list<data_>& other) {
				fprintf(stderr, "=> operator not yet implemented\n");
				exit(EXIT_FAILURE);
			}




			data_& operator [](signed long index) {
				try {
					this->peek(index);
					return this->frame->get_data_ref();
				}
				catch (std::range_error except) {
					throw except;
				}
			}





			/**
			 * @brief Check if the current linked list is empty or not.
			 * 
			 * @returns `(bool)` : true if the linked list is empty, false otherwise.
			*/
			bool empty() const {
				return (this->size == 0);
			}





			/**
			 * @brief Get the size of the linked list.
			 * 
			 * @returns `(unsigned long)` : The length of the linked list.
			*/
			unsigned long length() const {
				return this->size;
			}





			/**
			 * @brief Empties out the linked list and frees up memory.
			 * 
			 * @returns void.
			*/
			void reset() {
				// // std::cout << "Inside reset method" << // std::endl;
				this->frame = this->front;
				while (this->frame != nullptr) {
					this->front = this->frame->get_next();
					delete this->frame;
					this->frame = this->front;
				}
				this->size = 0;
			}





			/**
			 * @brief Push new data onto the linked list.
			 * 
			 * @note Can push to negative indexes. Negative indexes will push from the back of the list.
			 * 
			 * @param new_data `(Generic)` : The new data to be pushed onto the linked list.
			 * 
			 * @param index `(signed long)` : The index where the data should be pushed to. Defaults to -1.
			 * 
			 * @returns void.
			 * 
			 * @throws Throws a `std::range_error` if the index passed in references an index greater than the current size.
			 * 
			*/
			void push(data_ new_data, signed long index = -1) {
				unsigned long add_index = (index < 0) ? (this->size - (unsigned long) useful_functions::absolute<signed long>(index)) + 1 : (unsigned long) useful_functions::absolute<signed long>(index);
				if (add_index > this->size) {
					throw std::range_error("Cannot push data to negative index whose absolute value converts to a larger value than the size of the list");
				}
				
				linear_node<data_>* new_node = new linear_node<data_>(new_data);
				
				if (this->size == 0) {
					this->front = this->rear = this->frame = new_node;
				}

				else if (this->size == 1) {

					if (add_index == 0) {
						this->front->set_previous(new_node);
						this->front->get_previous()->set_next(this->front);
						this->front = this->front->get_previous();
						this->frame = this->front;
					}

					else {
						// index is 1
						this->rear->set_next(new_node);
						this->rear->get_next()->set_previous(this->rear);
						this->rear = this->rear->get_next();
						this->frame = this->rear;
					}
				}

				else {
					if (add_index == 0) {
						this->front->set_previous(new_node);
						this->front->get_previous()->set_next(this->front);
						this->front = this->front->get_previous();
						this->frame = this->front;
					}
					else if (add_index == this->size) {
						this->rear->set_next(new_node);
						this->rear->get_next()->set_previous(this->rear);
						this->rear = this->rear->get_next();
						this->frame = this->rear;
					}
					else {
						// this is where some extra work comes into play.
						signed long from_first = (signed long) add_index, from_rear = (signed long) (this->size - add_index), from_frame = (signed long) add_index - (signed long) add_index;
						unsigned long frame_abs = (from_frame < 0) ? ((unsigned long) (-1 * from_frame)) : (unsigned long) from_frame;
						signed long* signed_lists[] = {&from_first, &from_rear, &from_frame};
						useful_functions::selection_sort<signed long>(signed_lists, 3, true);
						
						if (signed_lists[0] == &from_first) {
							// shortest distance is from the front
							this->frame = this->front;
							this->frame_index = 0;
							this->frame_shifter(from_first);
						}
						else if (signed_lists[0] == &from_rear) {
							// shoftest distance is from the rear
							this->frame = this->rear;
							this->frame_index = this->size - 1;
							this->frame_shifter((signed long) ( -1 * from_rear));
						}
						else {
							// shortest distance is from the frame
							// fprintf(stdout, "Inside else branch of the push method. Pushing data towards the center of the list\n");
							this->frame_shifter(from_frame);
						}

						// Now frame should be at the proper index.
						new_node->set_previous(this->frame->get_previous());
						this->frame->get_previous()->set_next(new_node);
						this->frame->set_previous(new_node);
						new_node->set_next(this->frame);
						this->frame = this->frame->get_previous();

					}
				}
				this->size = this->size + 1;
			}





			/**
			 * @brief Peek at the data inside the linked list at a specific index.
			 * 
			 * @param index `(Generic)` : Defaults to -1. The index whose data is to be looked up.
			 * 
			 * @note This method can accept negative indexes. If the index references data 
			 * outside the range of the linked list, a length error is thrown.
			 * 
			 * @returns `(Generic)` : The data at the index specified.
			*/
			data_ peek(signed long index = -1) {
				unsigned long peek_index = (index < 0) ? (this->size - ((unsigned long) index) - 1) : (unsigned long) index;
				if (this->size == 0) {
					throw std::length_error("linear linked list is empty.");
				}
				if (peek_index == 0) {
					this->frame = this->front;
					this->frame_index = 0;
				}
				else if (peek_index == this->size - 1) {
					this->frame = this->rear;
					this->frame_index = this->size - 1;
				}
				else {
					// This is where some extra work comes into play.
					// this is constly on a smaller linked list,
					// but the payoff is big for a larger linked list.
					unsigned long from_first = peek_index, from_rear = this->size - 1 - peek_index, from_frame = ((signed long) peek_index - (signed long) this->frame_index);
					unsigned long* distances[] = {&from_first, &from_rear, &from_frame};
					useful_functions::insertion_sort<unsigned long>(distances, 3, true);
					if (distances[0] == &from_first) {
						this->frame = this->front;
						this->frame_index = 0;
						this->frame_shifter((signed long) from_first);
					}
					else if (distances[0] == &from_rear) {
						this->frame = this->rear;
						this->frame_index = this->size - 1;
						this->frame_shifter((signed long) from_rear);
					}
					else {
						// frame is the shortest distance to traverse
						this->frame_shifter((index < 0) ? ((signed long) from_frame * -1) : ((signed long) from_frame));
					}
				}
				// fprintf(stdout, "\tAbout to return %lu at index %lu\n", this->frame->get_data(), this->frame_index);
				return this->frame->get_data();
			}


	};


	template <typename data_> class binary_search_tree {

		private:
			unsigned long size;
			signed long height;
			bst_node<data_>* root;
		

			void push_new_data(bst_node<data_>* current, data_ new_data) {
				// fprintf(stdout, "Inside the push_new_data\n");
				if (current == nullptr) {
					return;
				}
				else if (new_data >= current->get_data()) {
					// go to the right of the current node.
					if (current->get_right_child() == nullptr) {
						// set the child here.
						current->set_right_child(new bst_node<data_>(new_data, current->get_height() + 1));
						current->get_right_child()->set_parent(current);
						this->size = this->size + 1;
						if (current->get_height() + 1 > this->height) {
							this->height = this->height + 1;
						}
						return;
					}
					this->push_new_data(current->get_right_child(), new_data);
				}
				else {
					// go to the left of the current node.
					if (current->get_left_child() == nullptr) {
						// set the child here
						current->set_left_child(new bst_node<data_>(new_data, current->get_height() + 1));
						current->get_left_child()->set_parent(current);
						this->size = this->size + 1;
						if (current->get_height() + 1 > this->height) {
							this->height = this->height + 1;
						}
						return;
					}
					this->push_new_data(current->get_left_child(), new_data);
				}
			}

			void update_heights(bst_node<data_>* current, signed long this_height) {
				if (current == nullptr) {
					return;
				}
				current->set_height(this_height);
				update_heights(current->get_left_child(), this_height + 1);
				update_heights(current->get_right_child(), this_height + 1);
				return;
			}

			void free_tree(bst_node<data_>* current) {
				if (current == nullptr) {
					return;
				}

				free_tree(current->get_left_child());
				free_tree(current->get_right_child());
				delete current;
			}

			signed long height_of(bst_node<data_>* current, data_ data) {
				if (current == nullptr) {
					return -1;
				}
				if (current->get_data() == data) {
					return this->get_height();
				}
				if (data > current->get_data()) {
					return this->height_of(current->get_right_child(), data);
				}
				return this->height_of(current->get_left_child(), data);
			}

			bst_node<data_>* get_most_child(bst_node<data_>* current, bool left = true) {
				if (current == nullptr) {
					return nullptr;
				}
				if (left) {
					if (current->get_left_child() == nullptr) {
						return current;
					}
					return this->get_most_child(current->get_left_child(), true);
				}
				else {
					if (current->get_right_child() == nullptr) {
						return current;
					}
					return this->get_most_child(current->get_right_child(), false);
				}
			}

			void update_node_heights(bst_node<data_>* current, signed long current_height) {
				if (current == nullptr) {
					return;
				}
				this->update_heights(current->get_left_child(), current_height + 1);
				this->update_heights(current->get_right_child(), current_height + 1);
				current->set_height(current_height);
			}

			void update_height(bst_node<data_>* current, signed long new_val) {
				if (current == nullptr) {
					return;
				}
				if (!current->get_left_child() && !current->get_right_child()) {
					this->height = new_val;
				}
				current->set_height(new_val);
				this->update_height(current->get_left_child(), new_val + 1);
				this->update_height(current->get_right_child(), new_val + 1);
			}

			void remove_node(bst_node<data_>* current, data_ remove_me) {
				
				// base case 1 : The data doesn't exist.
				if (current == nullptr) {
					return;
				}
				
				// base case 2: The data has been found
				if (current->get_data() == remove_me) {
					// There is a left child and a right child.
					if (current->get_left_child() && current->get_right_child()) {
						// get the left child's rightmost leaf.
						bst_node<data_>* right_most = this->get_most_child(current->get_left_child(), false);
						right_most->get_parent()->set_right_child(nullptr);
						current->set_data(right_most->get_data());
					}

					// There is only a left child and no right child.
					else if (current->get_left_child() && !current->get_right_child()) {
						bst_node<data_>* right_most = this->get_most_child(current->get_left_child(), false);
						right_most->get_parent()->set_right_child(nullptr);
						current->set_data(right_most->get_data());
					}

					// There is only a right child and no left child.
					else {
						bst_node<data_>* left_most = this->get_most_child(current->get_left_child(), true);
						left_most->get_parent()->set_right_child(nullptr);
						current->set_data(left_most->get_data());
					}
					this->size = this->size - 1;
					return;
				}

				// The data could be in the left or right child
				this->remove_node((remove_me >= current->get_data()) ? current->get_right_child() : current->get_left_child(), remove_me);
			}


		public:

			binary_search_tree() {
				this->size = 0;
				this->height = -1;
				this->root = nullptr;
			}


			binary_search_tree(data_ new_data) {
				this->root = new bst_node<data_>(new_data);
				this->root->set_height(0);
				this->size = 1;
				this->height = 0;
			}


			~binary_search_tree() {
				this->free_tree(this->root);
			}


			unsigned long get_height() const {
				return this->height;
			}

			signed long get_size() const {
				return this->size;
			}

			bool empty() const {
				return this->size == 0;
			}

			void add(data_ new_data) {
				if (this->size == 0) {
					this->root = new bst_node<data_>(new_data, 0);
					this->size = 1;
					this->height = 0;
				}
				else {
					this->push_new_data(this->root, new_data);
				}
			}

			bool contains(data_ to_find) {
				return this->height_of(this->root, to_find) != -1;
			}

			signed long data_height(data_ to_find) {
				return this->height_of(this->root, to_find);
			}


			void remove(data_ to_remove) {
				throw std::runtime_error("remove method not yet implemented");
				this->remove_node(this->root, to_remove);
			}


	};


}