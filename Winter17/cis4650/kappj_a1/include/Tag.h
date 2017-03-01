/* Tag.h                                                        */
/* Tag class definition                                         */
/* Created by Jeffrey-David Kapp; 0832671                       */
/* 1 Feburary 2017 - Last modifed 1/2/2017                      */

class Tag {
    public:
        tag_t tagType;
        string value;
        Tag ( string value );
        tag_t getTagType();
        string getValue();
    private:
        void NormaliseTag();
        void DetermineTagType();
};
