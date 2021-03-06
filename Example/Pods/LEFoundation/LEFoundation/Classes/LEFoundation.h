//
//  LEFoundation.h
//  Pods
//
//  Created by emerson larry on 2016/11/28.
//
//

#import <Foundation/Foundation.h>

#define LEWeakSelf(type)  __weak typeof(type) weak##type = type;

#define LESuppressPerformSelectorLeakWarning(Stuff) \
do { \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Warc-performSelector-leaks\"") \
Stuff; \
_Pragma("clang diagnostic pop") \
} while (0);

#define LESingleton_interface(className) \
+ (className *)sharedInstance;

#define LESingleton_implementation(className) \
static id _instace = nil; \
+ (instancetype)allocWithZone:(struct _NSZone *)zone \
{ \
if (_instace == nil) { \
static dispatch_once_t onceToken; \
dispatch_once(&onceToken, ^{ \
_instace = [super allocWithZone:zone]; \
}); \
} \
return _instace; \
} \
\
- (instancetype)init \
{ \
static dispatch_once_t onceToken; \
dispatch_once(&onceToken, ^{ \
_instace = [super init]; \
[_instace leExtraInits];\
}); \
return _instace; \
} \
\
+ (instancetype)sharedInstance \
{ \
return [[self alloc] init]; \
} \
+ (instancetype)copyWithZone:(struct _NSZone *)zone \
{ \
return _instace; \
} \
\
+ (instancetype)mutableCopyWithZone:(struct _NSZone *)zone \
{ \
return _instace; \
}

#pragma mark ? To String
#define LEIntToString(__int) [NSString stringWithFormat:@"%d",(int)__int]
#define LEIntegerToString(__integer) [NSString stringWithFormat:@"%zd",(NSInteger *)__integer]
#define LENumberToString(__number) [NSString stringWithFormat:@"%@",(NSNumber *)__number]
#define LEIntegerToInt(__integer) ((int)__integer)
#define LEFloatToString(__float) [NSString stringWithFormat:@"%f",(float)__float]
#pragma mark 数据存储
#define LEUserDefaults  [NSUserDefaults standardUserDefaults]
#define LECacheDir      [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject]
#define LEDocumentDir   [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject]
#define LETempDir       NSTemporaryDirectory()

#pragma mark Logs
#define LELogFunc   fprintf(stderr,"=> FUNC: %s\n",__FUNCTION__);
#define LELogObject(...) fprintf(stderr,"=> FUNC: %s %s\n",__FUNCTION__,[[NSString stringWithFormat:@"%@", ##__VA_ARGS__] UTF8String]);
#define LELogInt(...) fprintf(stderr,"=> FUNC: %s %s\n",__FUNCTION__,[[NSString stringWithFormat:@"%d", ##__VA_ARGS__] UTF8String]);
#define LELogInteger(...) fprintf(stderr,"=> FUNC: %s %s\n",__FUNCTION__,[[NSString stringWithFormat:@"%zd", ##__VA_ARGS__] UTF8String]);
#define LELogFloat(...) fprintf(stderr,"=> FUNC: %s %s\n",__FUNCTION__,[[NSString stringWithFormat:@"%f", ##__VA_ARGS__] UTF8String]);
#define LELogStringAndInt(...) fprintf(stderr,"=> FUNC: %s %s\n",__FUNCTION__,[[NSString stringWithFormat:@"%@ : %d", ##__VA_ARGS__] UTF8String]);
#define LELogStringAndInteger(...) fprintf(stderr,"=> FUNC: %s %s\n",__FUNCTION__,[[NSString stringWithFormat:@"%@ : %zd", ##__VA_ARGS__] UTF8String]);
#define LELogStringAndFloat(...) fprintf(stderr,"=> FUNC: %s %s\n",__FUNCTION__,[[NSString stringWithFormat:@"%@ : %f", ##__VA_ARGS__] UTF8String]);
#define LELogTwoObjects(...) fprintf(stderr,"=> FUNC: %s %s\n",__FUNCTION__,[[NSString stringWithFormat:@"@@\n-->%@\n-->%@", ##__VA_ARGS__] UTF8String]);
#define LELog(FORMAT, ...) fprintf(stderr,"=> (Line:%d) %s %s\n",__LINE__,__FUNCTION__,[[NSString stringWithFormat:FORMAT, ##__VA_ARGS__] UTF8String]);




@interface NSObject (LEFoundation)
/** 格式化为字符串 */
-(NSString *) leStringValue;
/**
 用于初始化，来自于NSObject意味着每个对象都可以实现该方法 */
-(void) leExtraInits;
/**
 用于给每个对象添加释放代码逻辑 */
-(void) leRelease;
/** 格式化为JSon数据 */
-(NSString*)    leObjToJSONString;
@end
@interface NSString (LEFoundation)
/** 字符串长度Ascii */
-(int)          leAsciiLength;
/** 字符串映射类对象 */
-(NSObject *)   leGetInstanceFromClassName;
/** 字符串映射类 */
-(Class) leClass;
/** 字符串去空格 */
-(NSString *)   leGetTrimmedString;
/** 字符串转Json数据（Array，Dictionary） */
-(id)           leJSONValue;
/** 字符串MD5加密 */
-(NSString *)   leMd5;
/** 字符串MD5+salt加密 */
-(NSString *)   leMd5WithSalt:(NSString *) salt;
/** 字符串64加密 */
-(NSString *)   leBase64Encoder;
/** 字符串64解密 */
-(NSString *)   leBase64Decoder;
@end
/** 封装模块留给外部的消息传递入口，可用于全局网络断开检测的消息提醒 */
@protocol LEAppMessageDelegate <NSObject>
-(void) leOnShowAppMessageWith:(NSString *) message;
@end


