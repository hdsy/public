// ***********************************************
// 创建日期： 2009-03-27
// 作    者： gaussgao
// 电子邮件： gycommunicate@vip.qq.com
// 主要功能： 实现对html文件的分析，查找和格式化
// ***********************************************


#include "CHtmlTagMap.h"

//##ModelId=49D46D6A01E4
CHtmlTagMap const& CHtmlTagMap::GetInstance()
{
	static CHtmlTagMap map;

	return map;
}

CHtmlTagMap::CHtmlTagMap()
{
//self
	insert(value_type("a"		 ,CTag("a"		  ,TAG_FORCE_SELF		,0	,"/a")));
	insert(value_type("script"   ,CTag("script"   ,TAG_FORCE_SELF		,0	,"/script")));

//none
	insert(value_type("!doctype"   ,CTag("!DOCTYPE"   ,TAG_NONE		,0	,"")));

	insert(value_type("base"   ,CTag("base"   ,TAG_NONE		,0	,"")));
	insert(value_type("area"   ,CTag("area"   ,TAG_NONE		,0	,"")));
	insert(value_type("basefont"   ,CTag("basefont"   ,TAG_NONE		,0	,"")));
	insert(value_type("br"   ,CTag("br"   ,TAG_NONE		,0	,"")));
	insert(value_type("col"   ,CTag("col"   ,TAG_NONE		,0	,"")));
	insert(value_type("hr"   ,CTag("hr"   ,TAG_NONE		,0	,"")));
	insert(value_type("img"   ,CTag("img"   ,TAG_NONE		,0	,"")));
	insert(value_type("input"   ,CTag("input"   ,TAG_NONE		,0	,"")));
	insert(value_type("keygen"   ,CTag("keygen"   ,TAG_NONE		,0	,"")));
	insert(value_type("link"   ,CTag("link"   ,TAG_NONE		,0	,"")));
	insert(value_type("meta"   ,CTag("meta"   ,TAG_NONE		,0	,"")));
	insert(value_type("nobr"   ,CTag("nobr"   ,TAG_NONE		,0	,"")));
	insert(value_type("param"   ,CTag("param"   ,TAG_NONE		,0	,"")));
	insert(value_type("plaintext"   ,CTag("plantext"   ,TAG_NONE		,0	,"")));
	insert(value_type("spacer"   ,CTag("spacer"   ,TAG_NONE		,0	,"")));
	insert(value_type("wbr"   ,CTag("wbr"   ,TAG_NONE		,0	,"")));

//xml 缺省使用
	//insert(value_type("br"   ,CTag("br"   ,TAG_FORCE_XML		,0	,"")));

	
//...
	//insert(value_type("br"   ,CTag("br"   ,TAG_PRIORITY		,0	,"")));

//special
	insert(value_type("tr"   ,CTag("tr"   ,TAG_SPECIAL		,0	,"tbody,/tbody,tfoot,/tfoot,/thead,tr,/tr,/table")));
	insert(value_type("thead"   ,CTag("thead"   ,TAG_SPECIAL		,0	,"tbody,tfoot,/thead")));
	insert(value_type("th"   ,CTag("th"   ,TAG_SPECIAL		,0	,"tbody,/tbody,tfoot,/tfoot,/thead,td,th,/th,tr,/tr,/table")));
	insert(value_type("tfoot"   ,CTag("tfoot"   ,TAG_SPECIAL		,0	,"tbody,/tfoot,thead")));
	insert(value_type("tbody"   ,CTag("tbody"   ,TAG_SPECIAL		,0	,"tbody,/tbody")));
	insert(value_type("td"   ,CTag("td"   ,TAG_SPECIAL		,0	,"tbody,/tbody,tfoot,/tfoot,/thead,td,/td,th,tr,/tr,/table")));
	insert(value_type("p"   ,CTag("p"   ,TAG_SPECIAL		,0	,"address,/address,applet,/applet,blockquote,/blockquote,/body,br,caption,/caption,center,/center,dd,/dd,div,/div,dl,/dl,dt,/dt,embed,/embed,form,/form,frame,/frame,frameset,/frameset,h1,/h1,h2,/h2,h3,/h3,h4,/h4,h5,/h5,h6,/h6,hr,/html,layer,/layer,li,/li,map,/map,multicol,/multicol,noembed, /noembed,noframes,/noframes,nolayer,/nolayer,noscript,/noscript,object,/object,ol,/ol,p,/p,plaintext,pre,/pre,script,/script,select,/select,style,/style,table,/table,tbody,/tbody,td,/td,tfoot,/tfootth,/th,thead,/theadtr,/tr,ul,/ul,xmp,/xmp")));
	insert(value_type("option"   ,CTag("option"   ,TAG_SPECIAL		,0	,"/optgroup,option,/option, lect")));
	insert(value_type("li"   ,CTag("li"   ,TAG_SPECIAL		,0	,"li,/li,/ol,/ul")));
	insert(value_type("head"   ,CTag("head"   ,TAG_SPECIAL		,0	,"body,/body,/head,/html")));
	insert(value_type("dt"   ,CTag("dt"   ,TAG_SPECIAL		,0	,"dt, /dt, /dl ")));
	insert(value_type("dd"   ,CTag("dd"   ,TAG_SPECIAL		,0	,"dd,/dd,/dl,dt,/dt")));
	insert(value_type("colgroup"   ,CTag("colgroup"   ,TAG_SPECIAL		,0	,"colgroup,/colgroup,tbody,tfoot,thead,tr,/table")));
	insert(value_type("body"   ,CTag("body"   ,TAG_SPECIAL		,0	,"/body,/html")));

}

