#ifndef __CUSTOMTABLEVIEWCELL_H__
#define __CUSTOMTABLEVIEWVELL_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

class CustomTableViewCell : public cocos2d::extension::TableViewCell
{
public:
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
};

#endif	/* __CUSTOMTABLEVIEWVELL_H__ */