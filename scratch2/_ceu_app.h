#ifndef _CEU_APP_H
#define _CEU_APP_H

#include "ceu_types.h"

#define CEU_INTS
#define CEU_EXTS
#define CEU_ORGS_AWAIT
#define CEU_ORGS_NEWS_MALLOC
#define CEU_ORGS_NEWS_POOL
#define CEU_CLEAR
#define CEU_ORGS
#define CEU_ORGS_NEWS
#define CEU_GOTO
#define CEU_STACK_CLEAR
     /* CEU_EXTS, CEU_WCLOCKS, CEU_INTS, ... */

/* TODO: lbl => unsigned */
#ifndef CEU_OS
typedef s16 tceu_nlbl;
#endif

#ifdef CEU_IFCS
/* (x) number of different classes */
typedef s16 tceu_ncls;
#endif

/* TODO: remove */
#define CEU_NTRAILS 13

#ifndef _CEU_OS_H
#define _CEU_OS_H

#include <stddef.h>
#include "ceu_types.h"

#ifdef CEU_DEBUG
#include <assert.h>
#endif

#if defined(CEU_OS) && defined(__AVR)
#error Understand this again!
#include "Arduino.h"
#define CEU_ISR
#define CEU_ISR_ON()  interrupts()
#define CEU_ISR_OFF() noInterrupts()
#else
#define CEU_ISR_ON()
#define CEU_ISR_OFF()
#endif

#if defined(CEU_OS_KERNEL) || defined(CEU_OS_APP)
#define CEU_OS
#endif

#if defined(CEU_ORGS_NEWS) || defined(CEU_ADTS_NEWS)
#define CEU_NEWS
#endif
#if defined(CEU_ORGS_NEWS_POOL) || defined(CEU_ADTS_NEWS_POOL)
#define CEU_NEWS_POOL
#endif
#if defined(CEU_ORGS_AWAIT) || defined(CEU_ADTS_AWAIT)
#define CEU_ORGS_OR_ADTS_AWAIT
#endif

#ifdef CEU_OS

    /* TODO: all should be configurable */
    #define CEU_EXTS
    #define CEU_WCLOCKS
    #define CEU_ASYNCS
    #define CEU_RET
    #define CEU_CLEAR
    #define CEU_STACK_CLEAR
#ifndef __AVR
#endif
    #define CEU_INTS
    #define CEU_ORGS
    /*#define CEU_PSES*/ /* TODO: never tried */
    #define CEU_NEWS
    #define CEU_NEWS_POOL
    #define CEU_ORGS_NEWS
    #define CEU_ORGS_NEWS_MALLOC
    #define CEU_ORGS_NEWS_POOL
    #define CEU_ADTS_NEWS
    #define CEU_ADTS_NEWS_MALLOC
    #define CEU_ADTS_NEWS_POOL
    #define CEU_ORGS_AWAIT
    #define CEU_ADTS_AWAIT
    #define CEU_ORGS_OR_ADTS_AWAIT
/*
    #define CEU_THREADS
*/

#ifdef __AVR
    #define CEU_QUEUE_MAX 256
#else
    #define CEU_QUEUE_MAX 65536
#endif

    #define CEU_IN__NONE          0
    #define CEU_IN__ORG         255
    #define CEU_IN__ORG_PSED    254
    #define CEU_IN__CLEAR       253
    #define CEU_IN__ok_killed   252
    #define CEU_IN__INIT        251     /* HIGHER EXTERNAL */
    #define CEU_IN__ASYNC       250
    #define CEU_IN__THREAD      249
    #define CEU_IN__WCLOCK      248
    #define CEU_IN_OS_START     247
    #define CEU_IN_OS_STOP      246
    #define CEU_IN_OS_DT        245
    #define CEU_IN_OS_INTERRUPT 244
#ifdef CEU_TIMEMACHINE
    #define CEU_IN__WCLOCK_     243
    #define CEU_IN              243
#else
    #define CEU_IN              242
#endif

    #define CEU_IN_higher       CEU_IN__INIT  /* _INIT = HIGHER EXTERNAL */
    #define CEU_IN_lower        128     /* TODO: not checked from up and down */

    typedef s8 tceu_nlbl;   /* TODO: to small!! */

#endif /* CEU_OS */

#ifdef CEU_OS_APP

    #define ceu_out_log(mode,str) \
        ((__typeof__(ceu_sys_log)*)((_ceu_app)->sys_vec[CEU_SYS_LOG]))(mode,str)

    #define ceu_out_assert(v) \
        ((__typeof__(ceu_sys_assert)*)((_ceu_app)->sys_vec[CEU_SYS_ASSERT]))(v)

    #define ceu_out_assert_msg_ex(v,msg,file,line)       \
        {                                                \
            int __ceu_v = v;                             \
            if ((!(__ceu_v)) && ((msg)!=NULL)) {         \
                ceu_out_log(0, (long)"[");               \
                ceu_out_log(0, (long)(file));            \
                ceu_out_log(0, (long)":");               \
                ceu_out_log(2, (line));                  \
                ceu_out_log(0, (long)"] ");              \
                ceu_out_log(0, (long)"runtime error: "); \
                ceu_out_log(0, (long)(msg));             \
                ceu_out_log(0, (long)"\n");              \
            }                                            \
            ((__typeof__(ceu_sys_assert)*)((_ceu_app)->sys_vec[CEU_SYS_ASSERT]))(__ceu_v); \
        }
    #define ceu_out_assert_msg(v,msg) ceu_out_assert_msg_ex((v),(msg),__FILE__,__LINE__)

    #define ceu_out_realloc(ptr, size) \
        ((__typeof__(ceu_sys_realloc)*)((_ceu_app)->sys_vec[CEU_SYS_REALLOC]))(ptr,size)

    #define ceu_out_req() \
        ((__typeof__(ceu_sys_req)*)((_ceu_app)->sys_vec[CEU_SYS_REQ]))()

    #define ceu_out_load(addr) \
        ((__typeof__(ceu_sys_load)*)((_ceu_app)->sys_vec[CEU_SYS_LOAD]))(addr)

#ifdef CEU_ISR
    #define ceu_out_isr(n,f) \
        ((__typeof__(ceu_sys_isr)*)((_ceu_app)->sys_vec[CEU_SYS_ISR]))(n,f,_ceu_app)
#endif

    #define ceu_out_org_init(app,org,n,lbl,cls,isDyn,parent_org,parent_trl) \
        ((__typeof__(ceu_sys_org_init)*)((app)->sys_vec[CEU_SYS_ORG]))(org,n,lbl,cls,isDyn,parent_org,parent_trl)
    #define ceu_out_start(app) \
        ((__typeof__(ceu_sys_start)*)((_ceu_app)->sys_vec[CEU_SYS_START]))(app)
    #define ceu_out_link(app1,evt1 , app2,evt2) \
        ((__typeof__(ceu_sys_link)*)((_ceu_app)->sys_vec[CEU_SYS_LINK]))(app1,evt1,app2,evt2)

    #define ceu_out_emit(app,id,sz,buf) \
        ((__typeof__(ceu_sys_emit)*)((app)->sys_vec[CEU_SYS_EMIT]))(app,id,sz,buf)

    #define ceu_out_call(app,id,param) \
        ((__typeof__(ceu_sys_call)*)((app)->sys_vec[CEU_SYS_CALL]))(app,id,param)

#ifdef CEU_WCLOCKS
    #define ceu_out_wclock(app,dt,set,get) \
        ((__typeof__(ceu_sys_wclock)*)((app)->sys_vec[CEU_SYS_WCLOCK]))(app,dt,set,get)
#ifdef CEU_TIMEMACHINE
    #error TIMEMACHINE
#endif
#endif

    #define ceu_out_go(app,evt,evtp) \
        ((__typeof__(ceu_sys_go)*)((app)->sys_vec[CEU_SYS_GO]))(app,evt,evtp)

#else /* ! CEU_OS_APP (!CEU_OS||CEU_OS_KERNEL) */

    #ifndef ceu_out_assert
        #error "Missing definition for macro \"ceu_out_assert\"."
    #endif

    #ifndef ceu_out_log
        #error "Missing definition for macro \"ceu_out_log\"."
    #endif

    #define ceu_out_assert_msg_ex(v,msg,file,line)          \
        {                                                   \
            int __ceu_v = v;                                \
            if ((!(__ceu_v)) && ((msg)!=NULL)) {            \
                ceu_out_log(0, (long)"[");                  \
                ceu_out_log(0, (long)(file));               \
                ceu_out_log(0, (long)":");                  \
                ceu_out_log(2, line);                       \
                ceu_out_log(0, (long)"] ");                 \
                ceu_out_log(0, (long)"runtime error: ");    \
                ceu_out_log(0, (long)(msg));                \
                ceu_out_log(0, (long)"\n");                 \
            }                                               \
            ceu_out_assert(__ceu_v);                        \
        }
    #define ceu_out_assert_msg(v,msg) ceu_out_assert_msg_ex((v),(msg),__FILE__,__LINE__)

    #define ceu_out_realloc(ptr,size) \
            ceu_sys_realloc(ptr,size)
    #define ceu_out_req() \
            ceu_sys_req()
    #define ceu_out_org_init(app,org,n,lbl,cls,isDyn,parent_org,parent_trl) \
            ceu_sys_org_init(org,n,lbl,cls,isDyn,parent_org,parent_trl)

#ifdef CEU_WCLOCKS
    #define ceu_out_wclock(app,dt,set,get) \
            ceu_sys_wclock(app,dt,set,get)
#ifdef CEU_TIMEMACHINE
    #define ceu_out_wclock_(app,dt,set,get) \
            ceu_sys_wclock_(app,dt,set,get)
#endif
#endif
    #define ceu_out_go(app,evt,evtp) \
            ceu_sys_go(app,evt,evtp)
    #define ceu_out_go_stk(app,evt,evtp,stk) \
            ceu_sys_go_stk(app,evt,evtp,stk)

#endif /* ! CEU_OS_APP (!CEU_OS||CEU_OS_KERNEL) */

#ifdef CEU_STACK_CLEAR
#define ceu_in_emit(app,id,n,buf) \
    ceu_out_go_stk(app,id,buf,&stk_)
#else
#define ceu_in_emit(app,id,n,buf) \
    ceu_out_go_stk(app,id,buf,NULL)
#endif

#ifdef CEU_THREADS
/* TODO: app */
#ifndef _CEU_THREADS_H
#define _CEU_THREADS_H

#include <pthread.h>
#define CEU_THREADS_T               pthread_t
#define CEU_THREADS_MUTEX_T         pthread_mutex_t
#define CEU_THREADS_COND_T          pthread_cond_t
#define CEU_THREADS_SELF()          pthread_self()
#define CEU_THREADS_CREATE(t,f,p)   pthread_create(t,NULL,f,p)
#define CEU_THREADS_DETACH(t)       pthread_detach(t)
/*
#define CEU_THREADS_MUTEX_LOCK(m)   pthread_mutex_lock(m); printf("L[%d]\n",__LINE__)
#define CEU_THREADS_MUTEX_UNLOCK(m) pthread_mutex_unlock(m); printf("U[%d]\n",__LINE__)
*/
#define CEU_THREADS_MUTEX_LOCK(m)   pthread_mutex_lock(m)
#define CEU_THREADS_MUTEX_UNLOCK(m) pthread_mutex_unlock(m);
/*
#define CEU_THREADS_COND_WAIT(c,m)  pthread_cond_wait(c,m)
#define CEU_THREADS_COND_SIGNAL(c)  pthread_cond_signal(c)
*/

#endif

#endif

#ifdef CEU_LUA
#include <stdio.h>      /* BUFSIZ */
#include <string.h>     /* strcpy */
#if defined(__ANDROID__) || defined(CEU_OS)
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
#else
    #include <lua5.1/lua.h>
    #include <lua5.1/lauxlib.h>
    #include <lua5.1/lualib.h>
#endif

#ifdef CEU_OS_APP
    #define ceu_luaL_newstate(set) { \
        set = ceu_out_call(_ceu_app, CEU_OUT_LUA_NEW, NULL); \
    }

    #define ceu_luaL_openlibs(l) { \
        lua_State* p = l;          \
        ceu_out_call(_ceu_app, CEU_OUT_LUAL_OPENLIBS, &p); \
    }

    #define ceu_lua_atpanic(l, f) {     \
    }

    #define ceu_luaL_loadstring(set, l, str) {  \
        tceu__lua_State___char_ p = { l, str }; \
        set = (int) ceu_out_call(_ceu_app, CEU_OUT_LUAL_LOADSTRING, &p); \
    }

    #define ceu_lua_pushnumber(l, v) {      \
        tceu__lua_State___int p = { l, v }; \
        ceu_out_call(_ceu_app, CEU_OUT_LUA_PUSHNUMBER, &p); \
    }

    #define ceu_lua_pushstring(l, v) {      \
        tceu__lua_State___char_ p = { l, v }; \
        ceu_out_call(_ceu_app, CEU_OUT_LUA_PUSHSTRING, &p); \
    }

    #define ceu_lua_pushlightuserdata(l, v) {   \
        tceu__lua_State___void_ p = { l, v };     \
        ceu_out_call(_ceu_app, CEU_OUT_LUA_PUSHLIGHTUSERDATA, &p); \
    }

    #define ceu_lua_pcall(set,l,nargs,nrets,err) {                  \
        tceu__lua_State___int__int__int p = { l, nargs, nrets, err }; \
        ceu_out_call(_ceu_app, CEU_OUT_LUA_PCALL, &p); \
    }

    #define ceu_lua_isnumber(set, l, idx) {     \
        tceu__lua_State___int p = { l, idx };   \
        set = (int) ceu_out_call(_ceu_app, CEU_OUT_LUA_ISNUMBER, &p); \
    }

    #define ceu_lua_tonumber(set, l, idx) {     \
        tceu__lua_State___int p = { l, idx };   \
        set = (int) ceu_out_call(_ceu_app, CEU_OUT_LUA_TONUMBER, &p); \
    }

    #define ceu_lua_isboolean(set, l, idx) {    \
        tceu__lua_State___int p = { l, idx };   \
        set = (int) ceu_out_call(_ceu_app, CEU_OUT_LUA_ISBOOLEAN, &p); \
    }

    #define ceu_lua_toboolean(set, l, idx) {    \
        tceu__lua_State___int p = { l, idx };   \
        set = (int) ceu_out_call(_ceu_app, CEU_OUT_LUA_TOBOOLEAN, &p); \
    }

    #define ceu_lua_pop(l, n) {             \
        tceu__lua_State___int p = { l, n }; \
        ceu_out_call(_ceu_app, CEU_OUT_LUA_POP, &p); \
    }

    #define ceu_lua_isstring(set, l, idx) {     \
        tceu__lua_State___int p = { l, idx };   \
        set = (int) ceu_out_call(_ceu_app, CEU_OUT_LUA_ISSTRING, &p); \
    }

    #define ceu_lua_tostring(set, l, idx) {     \
        tceu__lua_State___int p = { l, idx };   \
        set = ceu_out_call(_ceu_app, CEU_OUT_LUA_TOSTRING, &p); \
    }

    #define ceu_lua_islightuserdata(set, l, idx) {  \
        tceu__lua_State___int p = { l, idx };       \
        set = (int) ceu_out_call(_ceu_app, CEU_OUT_LUA_ISLIGHTUSERDATA, &p); \
    }

    #define ceu_lua_touserdata(set, l, idx) {   \
        tceu__lua_State___int p = { l, idx };   \
        set = ceu_out_call(_ceu_app, CEU_OUT_LUA_TOUSERDATA, &p); \
    }

    #define ceu_lua_error(l) {                          \
        lua_State** p = &l;                             \
        ceu_out_call(_ceu_app, CEU_OUT_LUA_ERROR, &p);  \
    }

    #define ceu_lua_objlen(set, l, idx) {                       \
        tceu__lua_State___int p = { l, idx };                   \
        set = ceu_out_call(_ceu_app, CEU_OUT_LUA_OBJLEN, &p);   \
    }

#else
    #define ceu_luaL_newstate(set)               set = luaL_newstate()
    #define ceu_luaL_openlibs(l)                 luaL_openlibs(l)
    #define ceu_lua_atpanic(l,f)                 lua_atpanic(l,f)
    #define ceu_luaL_loadstring(set,l,str)       set = luaL_loadstring(l,str)
    #define ceu_lua_pushnumber(l,v)              lua_pushnumber(l,v)
    #define ceu_lua_pushstring(l,v)              lua_pushstring(l,v)
    #define ceu_lua_pushlightuserdata(l,v)       lua_pushlightuserdata(l,v)
    #define ceu_lua_pcall(set,l,nargs,nrets,err) set = lua_pcall(l,nargs,nrets,err)
    #define ceu_lua_isnumber(set,l,idx)          set = lua_isnumber(l,idx)
    #define ceu_lua_tonumber(set,l,idx)          set = lua_tonumber(l,idx)
    #define ceu_lua_isboolean(set,l,idx)         set = lua_isboolean(l,idx)
    #define ceu_lua_toboolean(set,l,idx)         set = lua_toboolean(l,idx)
    #define ceu_lua_pop(l,n)                     lua_pop(l,n)
    #define ceu_lua_isstring(set,l,idx)          set = lua_isstring(l,idx)
    #define ceu_lua_tostring(set,l,idx)          set = lua_tostring(l,idx)
    #define ceu_lua_islightuserdata(set,l,idx)   set = lua_islightuserdata(l,idx)
    #define ceu_lua_touserdata(set,l,idx)        set = lua_touserdata(l,idx)
    #define ceu_lua_error(l)                     lua_error(l)
    #define ceu_lua_objlen(set,l,idx)            set = lua_objlen(l,idx)
#endif
#endif

typedef u8 tceu_nevt;   /* max number of events */
                        /* TODO: should "u8" be fixed? */

typedef u8 tceu_ntrl;   /* max number of trails per class */
                        /* TODO: should "u8" be fixed? */

#ifdef CEU_STACK_CLEAR
typedef u16 tceu_nstk;  /* max size of internal stack in bytes */
                        /* TODO: should "u16" be fixed? */
#endif

#ifdef __cplusplus
#define CEU_WCLOCK_INACTIVE 0x7fffffffL     /* TODO */
#else
#define CEU_WCLOCK_INACTIVE INT32_MAX
#endif
#define CEU_WCLOCK_EXPIRED (CEU_WCLOCK_INACTIVE-1)

/* TCEU_TRL */

struct tceu_org;
typedef union tceu_trl {
    tceu_nevt evt;

    /* normal await // IN__CLEAR */
    struct {                    /* TODO(ram): bitfields */
        tceu_nevt evt1;
        tceu_nlbl lbl;
        u8        seqno;        /* TODO(ram): 2 bits is enough */
#ifdef CEU_INTS                 /* R-9: size of trails for internal events */
#ifdef CEU_ORGS
        void*     evto;
#endif
#endif
    };

    /* IN__ORG */
#ifdef CEU_ORGS
    struct {                    /* TODO(ram): bad for alignment */
        tceu_nevt evt3;
        struct tceu_org* org;
    };
#endif

    /* _ok_killed */
#ifdef CEU_ORGS_OR_ADTS_AWAIT
    struct {
        tceu_nevt evt4;
        tceu_nlbl lbl4;
#ifdef CEU_ORGS_AWAIT
#ifdef CEU_ADTS_AWAIT
        u8        is_org;
#endif
#endif
        void*     org_or_adt;
    };
#endif
} tceu_trl;

/* TCEU_EVT */

typedef struct tceu_evt {
    tceu_nevt id;
    void*     param;
#if defined(CEU_ORGS) && defined(CEU_INTS)
    void*     org;      /* emitting org */
#endif
} tceu_evt;

/* TCEU_ORG */

struct tceu_pool_orgs;
typedef struct tceu_org
{
#ifdef CEU_ORGS
    struct tceu_org* nxt; /* first field because of free list for orgs/adts */
    struct tceu_org* prv;
    struct tceu_org* parent_org;
    tceu_ntrl parent_trl;
#endif

#if defined(CEU_ORGS) || defined(CEU_OS)
    tceu_ntrl n;            /* number of trails (TODO(ram): opt, metadata) */
#endif

#ifdef CEU_ORGS

#ifdef CEU_IFCS
    tceu_ncls cls;          /* class id */
#endif
    u8 isAlive: 1;          /* Three purposes:
                             * - avoids double free
                             * - required by "watching o" to avoid awaiting a
                             *      dead org
                             * - required by "Do T" to avoid awaiting a dead 
                             *      org
                             */
#if defined(CEU_ORGS_NEWS) || defined(CEU_ORGS_AWAIT)
#endif
#ifdef CEU_ORGS_NEWS
    u8 isDyn: 1;            /* created w/ new or spawn? */
#endif
#ifdef CEU_ORGS_NEWS_POOL
    struct tceu_pool_orgs* pool;
#endif

#ifdef CEU_ORGS_AWAIT
    int ret;
#endif

#endif  /* CEU_ORGS */

    tceu_trl trls[0];       /* first trail */

} tceu_org;

/* TCEU_POOL_ORGS , TCEU_POOL_ADTS */

#if defined(CEU_ORGS_NEWS_POOL) || defined(CEU_ADTS_NEWS_POOL)
#ifndef _CEU_POOL_H
#define _CEU_POOL_H

#include "ceu_types.h"

/* TODO: all "int" here, should evaluate the correct unsigned type */

typedef struct {
    byte**  queue;
                    /* queue is in the next offset to distinguish dynamic(NULL)
                       from static pools(any-address) */
    int     size;
    int     free;
    int     index;
    int     unit;
    byte*   mem;
} tceu_pool;

#define CEU_POOL_DCL(name, type, size) \
    type*     name##_queue[size];      \
    type      name##_mem[size];        \
    tceu_pool name;

void ceu_pool_init (tceu_pool* pool, int size, int unit, byte** queue, byte* mem);
byte* ceu_pool_alloc (tceu_pool* pool);
void ceu_pool_free (tceu_pool* pool, byte* val);

#endif

#endif

#ifdef CEU_ORGS_NEWS
typedef struct tceu_pool_orgs {
    tceu_org* parent_org;
    tceu_ntrl parent_trl;
#ifdef CEU_ORGS_NEWS_POOL
    tceu_pool pool;
#endif
} tceu_pool_orgs;
#endif

#ifdef CEU_ADTS_NEWS
typedef struct {
    void* root;
#ifdef CEU_ADTS_NEWS_POOL
    void* pool;
#endif
} tceu_pool_adts;
#endif

/* TCEU_KILL */

#ifdef CEU_ORGS_OR_ADTS_AWAIT
typedef struct tceu_kill {
    void*     org_or_adt;
    int       ret;
    tceu_ntrl t1;
    tceu_ntrl t2;
} tceu_kill;
#endif

/* TCEU_LST */

#ifdef CEU_DEBUG
typedef struct tceu_lst {
#ifdef CEU_ORGS
    void*     org;
#endif
    tceu_trl* trl;
    tceu_nlbl lbl;
} tceu_lst;

#endif

/* TCEU_STK */

#ifdef CEU_STACK_CLEAR
typedef struct tceu_stk {
    struct tceu_stk* down;
    tceu_org*   org;
    tceu_ntrl   trl1;
    tceu_ntrl   trl2;
    char        is_alive;
} tceu_stk;
#else
typedef void tceu_stk;
#endif

/* TCEU_APP */

typedef struct tceu_app {
    /* global seqno: incremented on every reaction
     * awaiting trails matches only if trl->seqno < seqno,
     * i.e., previously awaiting the event
     */
    u8 seqno:          2;
#if defined(CEU_RET) || defined(CEU_OS)
    u8 isAlive:        1;
#endif
#ifdef CEU_ASYNCS
    u8 pendingAsyncs:  1;
#endif
#if defined(CEU_ORGS_NEWS_MALLOC) && defined(CEU_ORGS_AWAIT)
    u8 dont_emit_kill: 1;
#endif

#ifdef CEU_OS
    struct tceu_app* nxt;
#endif

#if defined(CEU_RET) || defined(CEU_ORGS_AWAIT)
    int ret;
#endif

#ifdef CEU_ORGS_NEWS_MALLOC
    tceu_org* tofree;
#endif

#ifdef CEU_WCLOCKS
    s32         wclk_late;
    s32         wclk_min_set;   /* used to set */
    s32         wclk_min_cmp;   /* used to compare */
                                /* cmp<-set every reaction */
#ifdef CEU_TIMEMACHINE
    s32         wclk_late_;
    s32         wclk_min_set_;
    s32         wclk_min_cmp_;
#endif
#endif

#ifndef CEU_OS
#ifdef CEU_DEBUG
    tceu_lst    lst; /* segfault printf */
#endif
#endif

#ifdef CEU_THREADS
    CEU_THREADS_MUTEX_T threads_mutex;
    /*CEU_THREADS_COND_T  threads_cond;*/
    u8                  threads_n;          /* number of running threads */
        /* TODO: u8? */
#endif
#if defined(CEU_LUA) || defined(CEU_OS)
#ifdef CEU_LUA
    lua_State*  lua;    /* TODO: move to data? */
#else
    void*       lua;
#endif
#endif

    void        (*code)  (struct tceu_app*,tceu_evt*,tceu_org*,tceu_trl*,tceu_stk*);
    void        (*init)  (struct tceu_app*);
#ifdef CEU_OS
    void*       (*calls) (struct tceu_app*,tceu_nevt,void*);
    void**      sys_vec;
    void*       addr;
#ifdef CEU_OS_LUAIFC
    char*       luaifc;
#endif
#endif
    tceu_org*   data;
} tceu_app;

#ifdef CEU_OS
typedef void (*tceu_init)   (tceu_app* app);
typedef void (*tceu_export) (uint* size, tceu_init** init
#ifdef CEU_OS_LUAIFC
                            , char** luaifc
#endif
);
#endif

/* TCEU_THREADS_P */

#ifdef CEU_THREADS
typedef struct {
    tceu_app* app;
    tceu_org* org;
    s8*       st; /* thread state:
                   * 0=ini (sync  spawns)
                   * 1=cpy (async copies)
                   * 2=lck (sync  locks)
                   * 3=end (sync/async terminates)
                   */
} tceu_threads_p;
#endif

#ifdef CEU_PSES
void ceu_pause (tceu_trl* trl, tceu_trl* trlF, int psed);
#endif

int  ceu_go_all    (tceu_app* app);

#ifdef CEU_WCLOCKS
int       ceu_sys_wclock (tceu_app* app, s32 dt, s32* set, s32* get);
#endif
void      ceu_sys_go     (tceu_app* app, int evt, void* evtp);

#ifdef CEU_OS

/* TCEU_LINK */

typedef struct tceu_lnk {
    tceu_app* src_app;
    tceu_nevt src_evt;
    tceu_app* dst_app;
    tceu_nevt dst_evt;
    struct tceu_lnk* nxt;
} tceu_lnk;

/* TCEU_QUEUE */

typedef struct {
    tceu_app* app;
    tceu_nevt evt;
#if CEU_QUEUE_MAX == 256
    s8        sz;
#else
    s16       sz;   /* signed because of fill */
#endif
    byte      buf[0];
} tceu_queue;

#ifdef CEU_ISR
typedef void(*tceu_isr_f)(tceu_app* app, tceu_org* org);
#endif

void ceu_os_init      (void);
int  ceu_os_scheduler (int(*dt)());
tceu_queue* ceu_sys_queue_nxt (void);
void        ceu_sys_queue_rem (void);

void      ceu_sys_assert    (int v);
void      ceu_sys_log       (int mode, long str);
void*     ceu_sys_realloc   (void* ptr, size_t size);
int       ceu_sys_req       (void);
tceu_app* ceu_sys_load      (void* addr);
#ifdef CEU_ISR
int       ceu_sys_isr       (int n, tceu_isr_f f, tceu_app* app);
#endif
void      ceu_sys_org_init  (tceu_org* org, int n, int lbl, int cls, int isDyn,
                             tceu_org* parent_org, tceu_ntrl parent_trl);
void      ceu_sys_start     (tceu_app* app);
int       ceu_sys_link      (tceu_app* src_app, tceu_nevt src_evt, tceu_app* dst_app, tceu_nevt dst_evt);
int       ceu_sys_unlink    (tceu_app* src_app, tceu_nevt src_evt, tceu_app* dst_app, tceu_nevt dst_evt);
int       ceu_sys_emit      (tceu_app* app, tceu_nevt evt, int sz, void* param);
void*     ceu_sys_call      (tceu_app* app, tceu_nevt evt, void* param);

enum {
    CEU_SYS_ASSERT = 0,
    CEU_SYS_LOG,
    CEU_SYS_REALLOC,
    CEU_SYS_REQ,
    CEU_SYS_LOAD,
#ifdef CEU_ISR
    CEU_SYS_ISR,
#endif
#ifdef CEU_CLEAR
    CEU_SYS_CLEAR,
#endif
    CEU_SYS_STACK_PUSH,
#ifdef CEU_ORGS
    CEU_SYS_STACK_CLEAR_ORG,
#endif
    CEU_SYS_ORG,
#ifdef CEU_ORGS
    CEU_SYS_ORG_TRAIL,
    CEU_SYS_ORG_SPAWN,
#endif
    CEU_SYS_START,
    CEU_SYS_LINK,
    CEU_SYS_UNLINK,
    CEU_SYS_EMIT,
    CEU_SYS_CALL,
#ifdef CEU_WCLOCKS
    CEU_SYS_WCLOCK,
#endif
    CEU_SYS_GO,
    CEU_SYS_MAX
};

/* SYS_VECTOR
 */
extern void* CEU_SYS_VEC[CEU_SYS_MAX];

#endif  /* CEU_OS */

#endif  /* _CEU_OS_H */


#ifdef CEU_NEWS_POOL
#ifndef _CEU_POOL_H
#define _CEU_POOL_H

#include "ceu_types.h"

/* TODO: all "int" here, should evaluate the correct unsigned type */

typedef struct {
    byte**  queue;
                    /* queue is in the next offset to distinguish dynamic(NULL)
                       from static pools(any-address) */
    int     size;
    int     free;
    int     index;
    int     unit;
    byte*   mem;
} tceu_pool;

#define CEU_POOL_DCL(name, type, size) \
    type*     name##_queue[size];      \
    type      name##_mem[size];        \
    tceu_pool name;

void ceu_pool_init (tceu_pool* pool, int size, int unit, byte** queue, byte* mem);
byte* ceu_pool_alloc (tceu_pool* pool);
void ceu_pool_free (tceu_pool* pool, byte* val);

#endif

#endif

#ifdef CEU_VECTOR
#ifndef _CEU_VECTOR_H
#define _CEU_VECTOR_H

#ifndef _CEU_OS_H
#define _CEU_OS_H

#include <stddef.h>
#include "ceu_types.h"

#ifdef CEU_DEBUG
#include <assert.h>
#endif

#if defined(CEU_OS) && defined(__AVR)
#error Understand this again!
#include "Arduino.h"
#define CEU_ISR
#define CEU_ISR_ON()  interrupts()
#define CEU_ISR_OFF() noInterrupts()
#else
#define CEU_ISR_ON()
#define CEU_ISR_OFF()
#endif

#if defined(CEU_OS_KERNEL) || defined(CEU_OS_APP)
#define CEU_OS
#endif

#if defined(CEU_ORGS_NEWS) || defined(CEU_ADTS_NEWS)
#define CEU_NEWS
#endif
#if defined(CEU_ORGS_NEWS_POOL) || defined(CEU_ADTS_NEWS_POOL)
#define CEU_NEWS_POOL
#endif
#if defined(CEU_ORGS_AWAIT) || defined(CEU_ADTS_AWAIT)
#define CEU_ORGS_OR_ADTS_AWAIT
#endif

#ifdef CEU_OS

    /* TODO: all should be configurable */
    #define CEU_EXTS
    #define CEU_WCLOCKS
    #define CEU_ASYNCS
    #define CEU_RET
    #define CEU_CLEAR
    #define CEU_STACK_CLEAR
#ifndef __AVR
#endif
    #define CEU_INTS
    #define CEU_ORGS
    /*#define CEU_PSES*/ /* TODO: never tried */
    #define CEU_NEWS
    #define CEU_NEWS_POOL
    #define CEU_ORGS_NEWS
    #define CEU_ORGS_NEWS_MALLOC
    #define CEU_ORGS_NEWS_POOL
    #define CEU_ADTS_NEWS
    #define CEU_ADTS_NEWS_MALLOC
    #define CEU_ADTS_NEWS_POOL
    #define CEU_ORGS_AWAIT
    #define CEU_ADTS_AWAIT
    #define CEU_ORGS_OR_ADTS_AWAIT
/*
    #define CEU_THREADS
*/

#ifdef __AVR
    #define CEU_QUEUE_MAX 256
#else
    #define CEU_QUEUE_MAX 65536
#endif

    #define CEU_IN__NONE          0
    #define CEU_IN__ORG         255
    #define CEU_IN__ORG_PSED    254
    #define CEU_IN__CLEAR       253
    #define CEU_IN__ok_killed   252
    #define CEU_IN__INIT        251     /* HIGHER EXTERNAL */
    #define CEU_IN__ASYNC       250
    #define CEU_IN__THREAD      249
    #define CEU_IN__WCLOCK      248
    #define CEU_IN_OS_START     247
    #define CEU_IN_OS_STOP      246
    #define CEU_IN_OS_DT        245
    #define CEU_IN_OS_INTERRUPT 244
#ifdef CEU_TIMEMACHINE
    #define CEU_IN__WCLOCK_     243
    #define CEU_IN              243
#else
    #define CEU_IN              242
#endif

    #define CEU_IN_higher       CEU_IN__INIT  /* _INIT = HIGHER EXTERNAL */
    #define CEU_IN_lower        128     /* TODO: not checked from up and down */

    typedef s8 tceu_nlbl;   /* TODO: to small!! */

#endif /* CEU_OS */

#ifdef CEU_OS_APP

    #define ceu_out_log(mode,str) \
        ((__typeof__(ceu_sys_log)*)((_ceu_app)->sys_vec[CEU_SYS_LOG]))(mode,str)

    #define ceu_out_assert(v) \
        ((__typeof__(ceu_sys_assert)*)((_ceu_app)->sys_vec[CEU_SYS_ASSERT]))(v)

    #define ceu_out_assert_msg_ex(v,msg,file,line)       \
        {                                                \
            int __ceu_v = v;                             \
            if ((!(__ceu_v)) && ((msg)!=NULL)) {         \
                ceu_out_log(0, (long)"[");               \
                ceu_out_log(0, (long)(file));            \
                ceu_out_log(0, (long)":");               \
                ceu_out_log(2, (line));                  \
                ceu_out_log(0, (long)"] ");              \
                ceu_out_log(0, (long)"runtime error: "); \
                ceu_out_log(0, (long)(msg));             \
                ceu_out_log(0, (long)"\n");              \
            }                                            \
            ((__typeof__(ceu_sys_assert)*)((_ceu_app)->sys_vec[CEU_SYS_ASSERT]))(__ceu_v); \
        }
    #define ceu_out_assert_msg(v,msg) ceu_out_assert_msg_ex((v),(msg),__FILE__,__LINE__)

    #define ceu_out_realloc(ptr, size) \
        ((__typeof__(ceu_sys_realloc)*)((_ceu_app)->sys_vec[CEU_SYS_REALLOC]))(ptr,size)

    #define ceu_out_req() \
        ((__typeof__(ceu_sys_req)*)((_ceu_app)->sys_vec[CEU_SYS_REQ]))()

    #define ceu_out_load(addr) \
        ((__typeof__(ceu_sys_load)*)((_ceu_app)->sys_vec[CEU_SYS_LOAD]))(addr)

#ifdef CEU_ISR
    #define ceu_out_isr(n,f) \
        ((__typeof__(ceu_sys_isr)*)((_ceu_app)->sys_vec[CEU_SYS_ISR]))(n,f,_ceu_app)
#endif

    #define ceu_out_org_init(app,org,n,lbl,cls,isDyn,parent_org,parent_trl) \
        ((__typeof__(ceu_sys_org_init)*)((app)->sys_vec[CEU_SYS_ORG]))(org,n,lbl,cls,isDyn,parent_org,parent_trl)
    #define ceu_out_start(app) \
        ((__typeof__(ceu_sys_start)*)((_ceu_app)->sys_vec[CEU_SYS_START]))(app)
    #define ceu_out_link(app1,evt1 , app2,evt2) \
        ((__typeof__(ceu_sys_link)*)((_ceu_app)->sys_vec[CEU_SYS_LINK]))(app1,evt1,app2,evt2)

    #define ceu_out_emit(app,id,sz,buf) \
        ((__typeof__(ceu_sys_emit)*)((app)->sys_vec[CEU_SYS_EMIT]))(app,id,sz,buf)

    #define ceu_out_call(app,id,param) \
        ((__typeof__(ceu_sys_call)*)((app)->sys_vec[CEU_SYS_CALL]))(app,id,param)

#ifdef CEU_WCLOCKS
    #define ceu_out_wclock(app,dt,set,get) \
        ((__typeof__(ceu_sys_wclock)*)((app)->sys_vec[CEU_SYS_WCLOCK]))(app,dt,set,get)
#ifdef CEU_TIMEMACHINE
    #error TIMEMACHINE
#endif
#endif

    #define ceu_out_go(app,evt,evtp) \
        ((__typeof__(ceu_sys_go)*)((app)->sys_vec[CEU_SYS_GO]))(app,evt,evtp)

#else /* ! CEU_OS_APP (!CEU_OS||CEU_OS_KERNEL) */

    #ifndef ceu_out_assert
        #error "Missing definition for macro \"ceu_out_assert\"."
    #endif

    #ifndef ceu_out_log
        #error "Missing definition for macro \"ceu_out_log\"."
    #endif

    #define ceu_out_assert_msg_ex(v,msg,file,line)          \
        {                                                   \
            int __ceu_v = v;                                \
            if ((!(__ceu_v)) && ((msg)!=NULL)) {            \
                ceu_out_log(0, (long)"[");                  \
                ceu_out_log(0, (long)(file));               \
                ceu_out_log(0, (long)":");                  \
                ceu_out_log(2, line);                       \
                ceu_out_log(0, (long)"] ");                 \
                ceu_out_log(0, (long)"runtime error: ");    \
                ceu_out_log(0, (long)(msg));                \
                ceu_out_log(0, (long)"\n");                 \
            }                                               \
            ceu_out_assert(__ceu_v);                        \
        }
    #define ceu_out_assert_msg(v,msg) ceu_out_assert_msg_ex((v),(msg),__FILE__,__LINE__)

    #define ceu_out_realloc(ptr,size) \
            ceu_sys_realloc(ptr,size)
    #define ceu_out_req() \
            ceu_sys_req()
    #define ceu_out_org_init(app,org,n,lbl,cls,isDyn,parent_org,parent_trl) \
            ceu_sys_org_init(org,n,lbl,cls,isDyn,parent_org,parent_trl)

#ifdef CEU_WCLOCKS
    #define ceu_out_wclock(app,dt,set,get) \
            ceu_sys_wclock(app,dt,set,get)
#ifdef CEU_TIMEMACHINE
    #define ceu_out_wclock_(app,dt,set,get) \
            ceu_sys_wclock_(app,dt,set,get)
#endif
#endif
    #define ceu_out_go(app,evt,evtp) \
            ceu_sys_go(app,evt,evtp)
    #define ceu_out_go_stk(app,evt,evtp,stk) \
            ceu_sys_go_stk(app,evt,evtp,stk)

#endif /* ! CEU_OS_APP (!CEU_OS||CEU_OS_KERNEL) */

#ifdef CEU_STACK_CLEAR
#define ceu_in_emit(app,id,n,buf) \
    ceu_out_go_stk(app,id,buf,&stk_)
#else
#define ceu_in_emit(app,id,n,buf) \
    ceu_out_go_stk(app,id,buf,NULL)
#endif

#ifdef CEU_THREADS
/* TODO: app */
#include "ceu_threads.h"
#endif

#ifdef CEU_LUA
#include <stdio.h>      /* BUFSIZ */
#include <string.h>     /* strcpy */
#if defined(__ANDROID__) || defined(CEU_OS)
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
#else
    #include <lua5.1/lua.h>
    #include <lua5.1/lauxlib.h>
    #include <lua5.1/lualib.h>
#endif

#ifdef CEU_OS_APP
    #define ceu_luaL_newstate(set) { \
        set = ceu_out_call(_ceu_app, CEU_OUT_LUA_NEW, NULL); \
    }

    #define ceu_luaL_openlibs(l) { \
        lua_State* p = l;          \
        ceu_out_call(_ceu_app, CEU_OUT_LUAL_OPENLIBS, &p); \
    }

    #define ceu_lua_atpanic(l, f) {     \
    }

    #define ceu_luaL_loadstring(set, l, str) {  \
        tceu__lua_State___char_ p = { l, str }; \
        set = (int) ceu_out_call(_ceu_app, CEU_OUT_LUAL_LOADSTRING, &p); \
    }

    #define ceu_lua_pushnumber(l, v) {      \
        tceu__lua_State___int p = { l, v }; \
        ceu_out_call(_ceu_app, CEU_OUT_LUA_PUSHNUMBER, &p); \
    }

    #define ceu_lua_pushstring(l, v) {      \
        tceu__lua_State___char_ p = { l, v }; \
        ceu_out_call(_ceu_app, CEU_OUT_LUA_PUSHSTRING, &p); \
    }

    #define ceu_lua_pushlightuserdata(l, v) {   \
        tceu__lua_State___void_ p = { l, v };     \
        ceu_out_call(_ceu_app, CEU_OUT_LUA_PUSHLIGHTUSERDATA, &p); \
    }

    #define ceu_lua_pcall(set,l,nargs,nrets,err) {                  \
        tceu__lua_State___int__int__int p = { l, nargs, nrets, err }; \
        ceu_out_call(_ceu_app, CEU_OUT_LUA_PCALL, &p); \
    }

    #define ceu_lua_isnumber(set, l, idx) {     \
        tceu__lua_State___int p = { l, idx };   \
        set = (int) ceu_out_call(_ceu_app, CEU_OUT_LUA_ISNUMBER, &p); \
    }

    #define ceu_lua_tonumber(set, l, idx) {     \
        tceu__lua_State___int p = { l, idx };   \
        set = (int) ceu_out_call(_ceu_app, CEU_OUT_LUA_TONUMBER, &p); \
    }

    #define ceu_lua_isboolean(set, l, idx) {    \
        tceu__lua_State___int p = { l, idx };   \
        set = (int) ceu_out_call(_ceu_app, CEU_OUT_LUA_ISBOOLEAN, &p); \
    }

    #define ceu_lua_toboolean(set, l, idx) {    \
        tceu__lua_State___int p = { l, idx };   \
        set = (int) ceu_out_call(_ceu_app, CEU_OUT_LUA_TOBOOLEAN, &p); \
    }

    #define ceu_lua_pop(l, n) {             \
        tceu__lua_State___int p = { l, n }; \
        ceu_out_call(_ceu_app, CEU_OUT_LUA_POP, &p); \
    }

    #define ceu_lua_isstring(set, l, idx) {     \
        tceu__lua_State___int p = { l, idx };   \
        set = (int) ceu_out_call(_ceu_app, CEU_OUT_LUA_ISSTRING, &p); \
    }

    #define ceu_lua_tostring(set, l, idx) {     \
        tceu__lua_State___int p = { l, idx };   \
        set = ceu_out_call(_ceu_app, CEU_OUT_LUA_TOSTRING, &p); \
    }

    #define ceu_lua_islightuserdata(set, l, idx) {  \
        tceu__lua_State___int p = { l, idx };       \
        set = (int) ceu_out_call(_ceu_app, CEU_OUT_LUA_ISLIGHTUSERDATA, &p); \
    }

    #define ceu_lua_touserdata(set, l, idx) {   \
        tceu__lua_State___int p = { l, idx };   \
        set = ceu_out_call(_ceu_app, CEU_OUT_LUA_TOUSERDATA, &p); \
    }

    #define ceu_lua_error(l) {                          \
        lua_State** p = &l;                             \
        ceu_out_call(_ceu_app, CEU_OUT_LUA_ERROR, &p);  \
    }

    #define ceu_lua_objlen(set, l, idx) {                       \
        tceu__lua_State___int p = { l, idx };                   \
        set = ceu_out_call(_ceu_app, CEU_OUT_LUA_OBJLEN, &p);   \
    }

#else
    #define ceu_luaL_newstate(set)               set = luaL_newstate()
    #define ceu_luaL_openlibs(l)                 luaL_openlibs(l)
    #define ceu_lua_atpanic(l,f)                 lua_atpanic(l,f)
    #define ceu_luaL_loadstring(set,l,str)       set = luaL_loadstring(l,str)
    #define ceu_lua_pushnumber(l,v)              lua_pushnumber(l,v)
    #define ceu_lua_pushstring(l,v)              lua_pushstring(l,v)
    #define ceu_lua_pushlightuserdata(l,v)       lua_pushlightuserdata(l,v)
    #define ceu_lua_pcall(set,l,nargs,nrets,err) set = lua_pcall(l,nargs,nrets,err)
    #define ceu_lua_isnumber(set,l,idx)          set = lua_isnumber(l,idx)
    #define ceu_lua_tonumber(set,l,idx)          set = lua_tonumber(l,idx)
    #define ceu_lua_isboolean(set,l,idx)         set = lua_isboolean(l,idx)
    #define ceu_lua_toboolean(set,l,idx)         set = lua_toboolean(l,idx)
    #define ceu_lua_pop(l,n)                     lua_pop(l,n)
    #define ceu_lua_isstring(set,l,idx)          set = lua_isstring(l,idx)
    #define ceu_lua_tostring(set,l,idx)          set = lua_tostring(l,idx)
    #define ceu_lua_islightuserdata(set,l,idx)   set = lua_islightuserdata(l,idx)
    #define ceu_lua_touserdata(set,l,idx)        set = lua_touserdata(l,idx)
    #define ceu_lua_error(l)                     lua_error(l)
    #define ceu_lua_objlen(set,l,idx)            set = lua_objlen(l,idx)
#endif
#endif

typedef u8 tceu_nevt;   /* max number of events */
                        /* TODO: should "u8" be fixed? */

typedef u8 tceu_ntrl;   /* max number of trails per class */
                        /* TODO: should "u8" be fixed? */

#ifdef CEU_STACK_CLEAR
typedef u16 tceu_nstk;  /* max size of internal stack in bytes */
                        /* TODO: should "u16" be fixed? */
#endif

#ifdef __cplusplus
#define CEU_WCLOCK_INACTIVE 0x7fffffffL     /* TODO */
#else
#define CEU_WCLOCK_INACTIVE INT32_MAX
#endif
#define CEU_WCLOCK_EXPIRED (CEU_WCLOCK_INACTIVE-1)

/* TCEU_TRL */

struct tceu_org;
typedef union tceu_trl {
    tceu_nevt evt;

    /* normal await // IN__CLEAR */
    struct {                    /* TODO(ram): bitfields */
        tceu_nevt evt1;
        tceu_nlbl lbl;
        u8        seqno;        /* TODO(ram): 2 bits is enough */
#ifdef CEU_INTS                 /* R-9: size of trails for internal events */
#ifdef CEU_ORGS
        void*     evto;
#endif
#endif
    };

    /* IN__ORG */
#ifdef CEU_ORGS
    struct {                    /* TODO(ram): bad for alignment */
        tceu_nevt evt3;
        struct tceu_org* org;
    };
#endif

    /* _ok_killed */
#ifdef CEU_ORGS_OR_ADTS_AWAIT
    struct {
        tceu_nevt evt4;
        tceu_nlbl lbl4;
#ifdef CEU_ORGS_AWAIT
#ifdef CEU_ADTS_AWAIT
        u8        is_org;
#endif
#endif
        void*     org_or_adt;
    };
#endif
} tceu_trl;

/* TCEU_EVT */

typedef struct tceu_evt {
    tceu_nevt id;
    void*     param;
#if defined(CEU_ORGS) && defined(CEU_INTS)
    void*     org;      /* emitting org */
#endif
} tceu_evt;

/* TCEU_ORG */

struct tceu_pool_orgs;
typedef struct tceu_org
{
#ifdef CEU_ORGS
    struct tceu_org* nxt; /* first field because of free list for orgs/adts */
    struct tceu_org* prv;
    struct tceu_org* parent_org;
    tceu_ntrl parent_trl;
#endif

#if defined(CEU_ORGS) || defined(CEU_OS)
    tceu_ntrl n;            /* number of trails (TODO(ram): opt, metadata) */
#endif

#ifdef CEU_ORGS

#ifdef CEU_IFCS
    tceu_ncls cls;          /* class id */
#endif
    u8 isAlive: 1;          /* Three purposes:
                             * - avoids double free
                             * - required by "watching o" to avoid awaiting a
                             *      dead org
                             * - required by "Do T" to avoid awaiting a dead 
                             *      org
                             */
#if defined(CEU_ORGS_NEWS) || defined(CEU_ORGS_AWAIT)
#endif
#ifdef CEU_ORGS_NEWS
    u8 isDyn: 1;            /* created w/ new or spawn? */
#endif
#ifdef CEU_ORGS_NEWS_POOL
    struct tceu_pool_orgs* pool;
#endif

#ifdef CEU_ORGS_AWAIT
    int ret;
#endif

#endif  /* CEU_ORGS */

    tceu_trl trls[0];       /* first trail */

} tceu_org;

/* TCEU_POOL_ORGS , TCEU_POOL_ADTS */

#if defined(CEU_ORGS_NEWS_POOL) || defined(CEU_ADTS_NEWS_POOL)
#include "ceu_pool.h"
#endif

#ifdef CEU_ORGS_NEWS
typedef struct tceu_pool_orgs {
    tceu_org* parent_org;
    tceu_ntrl parent_trl;
#ifdef CEU_ORGS_NEWS_POOL
    tceu_pool pool;
#endif
} tceu_pool_orgs;
#endif

#ifdef CEU_ADTS_NEWS
typedef struct {
    void* root;
#ifdef CEU_ADTS_NEWS_POOL
    void* pool;
#endif
} tceu_pool_adts;
#endif

/* TCEU_KILL */

#ifdef CEU_ORGS_OR_ADTS_AWAIT
typedef struct tceu_kill {
    void*     org_or_adt;
    int       ret;
    tceu_ntrl t1;
    tceu_ntrl t2;
} tceu_kill;
#endif

/* TCEU_LST */

#ifdef CEU_DEBUG
typedef struct tceu_lst {
#ifdef CEU_ORGS
    void*     org;
#endif
    tceu_trl* trl;
    tceu_nlbl lbl;
} tceu_lst;

#endif

/* TCEU_STK */

#ifdef CEU_STACK_CLEAR
typedef struct tceu_stk {
    struct tceu_stk* down;
    tceu_org*   org;
    tceu_ntrl   trl1;
    tceu_ntrl   trl2;
    char        is_alive;
} tceu_stk;
#else
typedef void tceu_stk;
#endif

/* TCEU_APP */

typedef struct tceu_app {
    /* global seqno: incremented on every reaction
     * awaiting trails matches only if trl->seqno < seqno,
     * i.e., previously awaiting the event
     */
    u8 seqno:          2;
#if defined(CEU_RET) || defined(CEU_OS)
    u8 isAlive:        1;
#endif
#ifdef CEU_ASYNCS
    u8 pendingAsyncs:  1;
#endif
#if defined(CEU_ORGS_NEWS_MALLOC) && defined(CEU_ORGS_AWAIT)
    u8 dont_emit_kill: 1;
#endif

#ifdef CEU_OS
    struct tceu_app* nxt;
#endif

#if defined(CEU_RET) || defined(CEU_ORGS_AWAIT)
    int ret;
#endif

#ifdef CEU_ORGS_NEWS_MALLOC
    tceu_org* tofree;
#endif

#ifdef CEU_WCLOCKS
    s32         wclk_late;
    s32         wclk_min_set;   /* used to set */
    s32         wclk_min_cmp;   /* used to compare */
                                /* cmp<-set every reaction */
#ifdef CEU_TIMEMACHINE
    s32         wclk_late_;
    s32         wclk_min_set_;
    s32         wclk_min_cmp_;
#endif
#endif

#ifndef CEU_OS
#ifdef CEU_DEBUG
    tceu_lst    lst; /* segfault printf */
#endif
#endif

#ifdef CEU_THREADS
    CEU_THREADS_MUTEX_T threads_mutex;
    /*CEU_THREADS_COND_T  threads_cond;*/
    u8                  threads_n;          /* number of running threads */
        /* TODO: u8? */
#endif
#if defined(CEU_LUA) || defined(CEU_OS)
#ifdef CEU_LUA
    lua_State*  lua;    /* TODO: move to data? */
#else
    void*       lua;
#endif
#endif

    void        (*code)  (struct tceu_app*,tceu_evt*,tceu_org*,tceu_trl*,tceu_stk*);
    void        (*init)  (struct tceu_app*);
#ifdef CEU_OS
    void*       (*calls) (struct tceu_app*,tceu_nevt,void*);
    void**      sys_vec;
    void*       addr;
#ifdef CEU_OS_LUAIFC
    char*       luaifc;
#endif
#endif
    tceu_org*   data;
} tceu_app;

#ifdef CEU_OS
typedef void (*tceu_init)   (tceu_app* app);
typedef void (*tceu_export) (uint* size, tceu_init** init
#ifdef CEU_OS_LUAIFC
                            , char** luaifc
#endif
);
#endif

/* TCEU_THREADS_P */

#ifdef CEU_THREADS
typedef struct {
    tceu_app* app;
    tceu_org* org;
    s8*       st; /* thread state:
                   * 0=ini (sync  spawns)
                   * 1=cpy (async copies)
                   * 2=lck (sync  locks)
                   * 3=end (sync/async terminates)
                   */
} tceu_threads_p;
#endif

#ifdef CEU_PSES
void ceu_pause (tceu_trl* trl, tceu_trl* trlF, int psed);
#endif

int  ceu_go_all    (tceu_app* app);

#ifdef CEU_WCLOCKS
int       ceu_sys_wclock (tceu_app* app, s32 dt, s32* set, s32* get);
#endif
void      ceu_sys_go     (tceu_app* app, int evt, void* evtp);

#ifdef CEU_OS

/* TCEU_LINK */

typedef struct tceu_lnk {
    tceu_app* src_app;
    tceu_nevt src_evt;
    tceu_app* dst_app;
    tceu_nevt dst_evt;
    struct tceu_lnk* nxt;
} tceu_lnk;

/* TCEU_QUEUE */

typedef struct {
    tceu_app* app;
    tceu_nevt evt;
#if CEU_QUEUE_MAX == 256
    s8        sz;
#else
    s16       sz;   /* signed because of fill */
#endif
    byte      buf[0];
} tceu_queue;

#ifdef CEU_ISR
typedef void(*tceu_isr_f)(tceu_app* app, tceu_org* org);
#endif

void ceu_os_init      (void);
int  ceu_os_scheduler (int(*dt)());
tceu_queue* ceu_sys_queue_nxt (void);
void        ceu_sys_queue_rem (void);

void      ceu_sys_assert    (int v);
void      ceu_sys_log       (int mode, long str);
void*     ceu_sys_realloc   (void* ptr, size_t size);
int       ceu_sys_req       (void);
tceu_app* ceu_sys_load      (void* addr);
#ifdef CEU_ISR
int       ceu_sys_isr       (int n, tceu_isr_f f, tceu_app* app);
#endif
void      ceu_sys_org_init  (tceu_org* org, int n, int lbl, int cls, int isDyn,
                             tceu_org* parent_org, tceu_ntrl parent_trl);
void      ceu_sys_start     (tceu_app* app);
int       ceu_sys_link      (tceu_app* src_app, tceu_nevt src_evt, tceu_app* dst_app, tceu_nevt dst_evt);
int       ceu_sys_unlink    (tceu_app* src_app, tceu_nevt src_evt, tceu_app* dst_app, tceu_nevt dst_evt);
int       ceu_sys_emit      (tceu_app* app, tceu_nevt evt, int sz, void* param);
void*     ceu_sys_call      (tceu_app* app, tceu_nevt evt, void* param);

enum {
    CEU_SYS_ASSERT = 0,
    CEU_SYS_LOG,
    CEU_SYS_REALLOC,
    CEU_SYS_REQ,
    CEU_SYS_LOAD,
#ifdef CEU_ISR
    CEU_SYS_ISR,
#endif
#ifdef CEU_CLEAR
    CEU_SYS_CLEAR,
#endif
    CEU_SYS_STACK_PUSH,
#ifdef CEU_ORGS
    CEU_SYS_STACK_CLEAR_ORG,
#endif
    CEU_SYS_ORG,
#ifdef CEU_ORGS
    CEU_SYS_ORG_TRAIL,
    CEU_SYS_ORG_SPAWN,
#endif
    CEU_SYS_START,
    CEU_SYS_LINK,
    CEU_SYS_UNLINK,
    CEU_SYS_EMIT,
    CEU_SYS_CALL,
#ifdef CEU_WCLOCKS
    CEU_SYS_WCLOCK,
#endif
    CEU_SYS_GO,
    CEU_SYS_MAX
};

/* SYS_VECTOR
 */
extern void* CEU_SYS_VEC[CEU_SYS_MAX];

#endif  /* CEU_OS */

#endif  /* _CEU_OS_H */


typedef struct {
    int   max;
    int   nxt;
    int   unit;
    byte* mem;
} tceu_vector;

#define CEU_VECTOR_DCL(name, type, max)  \
    type        name##_mem[max+1];       \
    tceu_vector name;
                /* [STRING] max+1: extra space for '\0' */

#define ceu_vector_getlen(vec) ((vec)->nxt)
#define ceu_vector_getmax(vec) ((vec)->max > 0 ? (vec)->max : 0)

void  ceu_vector_init   (tceu_vector* vector, int max, int unit, byte* mem);
int   ceu_vector_setlen (tceu_vector* vector, int len);
byte* ceu_vector_geti   (tceu_vector* vector, int idx);
int   ceu_vector_seti   (tceu_vector* vector, int idx, byte* v);
int   ceu_vector_push   (tceu_vector* vector, byte* v);
int   ceu_vector_concat (tceu_vector* to, tceu_vector* fr);
int   ceu_vector_concat_buffer (tceu_vector* to, const char* fr, int n);
char* ceu_vector_tochar (tceu_vector* vector);

#if 0
byte* ceu_pool_alloc (tceu_pool* pool);
void ceu_pool_free (tceu_pool* pool, byte* val);
#endif
#endif

#endif


#define CEU_IN__NONE 0
#define CEU_IN__ORG 255
#define CEU_IN__ORG_PSED 254
#define CEU_IN__CLEAR 253
#define CEU_IN__ok_killed 252
#define CEU_IN__INIT 251
#define CEU_IN__ASYNC 250
#define CEU_IN__THREAD 249
#define CEU_IN__WCLOCK 248
#define CEU_IN_KEY_DOWN 247
#define CEU_IN_KEY_UP 246
#define CEU_IN_UPDATE 245
#define CEU_IN_MOUSE_DOWN 244
#define CEU_IN_MOUSE_UP 243
#define CEU_IN_MOUSE_OVER 242
#define CEU_IN_MOUSE_OUT 241
#define CEU_IN_MOUSE_MOVE 240
#define CEU_OUT_NEW_SPRITE 1
#define CEU_OUT_FREE_SPRITE 2
#define CEU_OUT_SET_SPRITE_POSITION 3
#define CEU_OUT_SET_SPRITE_TINT 4
#define CEU_OUT_SET_SPRITE_ROTATION 5
#define CEU_OUT_SET_COUNT 6
#define CEU_OUT_SET_MUTED 7
#define CEU_OUT_PRINT_DEBUG 8
#define CEU_IN_higher CEU_IN__INIT
#define CEU_IN_lower 240
#define CEU_OUT_n 8
      /* CEU_IN_, CEU_OUT_ */
#define CEU_FUN_sqrt
#define CEU_FUN_printf
#define CEU_FUN_d
   /* CEU_FUN_ */
typedef struct {
	int _1;
	int _2;
} tceu__int__int;
typedef struct {
	charptr _1;
} tceu__charptr;
typedef struct {
	int _1;
	float _2;
} tceu__int__float;
typedef struct {
	int _1;
} tceu__int;
typedef struct {
	int _1;
	int _2;
	int _3;
	int _4;
} tceu__int__int__int__int;
typedef struct {
	int _1;
	int _2;
	int _3;
	int _4;
	int _5;
} tceu__int__int__int__int__int;
typedef struct {
	bool _1;
} tceu__bool;
typedef struct {
	s32 _1;
} tceu__s32;


/* class/adts definitions */
/* may use types defined above in "NATIVE" */
/* each class may define new native code that appear after its struct declaration */

typedef struct CEU_Delay {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 2 ];
                            struct { /* BLOCK ln=49 */
                              int ticks;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=49 */
                                  union {
                                    struct { /* BLOCK ln=53 */
                                      int ticker;
                                      union {
                                        union {
                                        };
                                        struct { /* BLOCK ln=54 */
                                          union {
                                            union {
                                            };
                                              struct { /* BLOCK ln=55 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=57 */
                                                      union {
                                                      };
                                                    } ;
                                                    struct { /* BLOCK ln=59 */
                                                      union {
                                                      };
                                                    } ;
                                                };
                                              } ;
                                          };
                                        } ;
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_Delay;





typedef struct CEU_Garden {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 3 ];
                            struct { /* BLOCK ln=65 */
                              float score;
                              int t0_plants;
                              int t1_plants;
                              int t2_plants;
                              int t3_plants;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=65 */
                                  union {
                                    struct { /* BLOCK ln=75 */
                                      union {
                                        struct { /* BLOCK ln=75 */
                                          union {
                                            union {
                                            };
                                              struct { /* BLOCK ln=76 */
                                                union {
                                                    struct { /* BLOCK ln=76 */
                                                      struct CEU_Delay _org_156_11;
                                                      union {
                                                            struct { /* BLOCK ln=77 */
                                                              union {
                                                              };
                                                            } ;
                                                        union {
                                                          union {
                                                              struct { /* BLOCK ln=76 */
                                                                union {
                                                                };
                                                              } ;
                                                              struct { /* BLOCK ln=76 */
                                                                union {
                                                                };
                                                              } ;
                                                          };
                                                        };
                                                      };
                                                    } ;
                                                };
                                              } ;
                                          };
                                        } ;
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_Garden;





typedef struct CEU_Konami {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 2 ];
                            struct { /* BLOCK ln=83 */
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=83 */
                                  union {
                                    struct { /* BLOCK ln=86 */
                                      union {
                                        struct { /* BLOCK ln=86 */
                                          union {
                                            union {
                                            };
                                              struct { /* BLOCK ln=87 */
                                                union {
                                                  union {
                                                    union {
                                                    };
                                                  };
                                                    struct { /* BLOCK ln=88 */
                                                      union {
                                                      };
                                                    } ;
                                                    struct { /* BLOCK ln=86 */
                                                      union {
                                                        union {
                                                        };
                                                          struct { /* BLOCK ln=90 */
                                                            union {
                                                            };
                                                          } ;
                                                          struct { /* BLOCK ln=86 */
                                                            union {
                                                              union {
                                                              };
                                                                struct { /* BLOCK ln=92 */
                                                                  union {
                                                                  };
                                                                } ;
                                                                struct { /* BLOCK ln=86 */
                                                                  union {
                                                                    union {
                                                                    };
                                                                      struct { /* BLOCK ln=94 */
                                                                        union {
                                                                        };
                                                                      } ;
                                                                      struct { /* BLOCK ln=86 */
                                                                        union {
                                                                          union {
                                                                          };
                                                                            struct { /* BLOCK ln=96 */
                                                                              union {
                                                                              };
                                                                            } ;
                                                                            struct { /* BLOCK ln=86 */
                                                                              union {
                                                                                union {
                                                                                };
                                                                                  struct { /* BLOCK ln=98 */
                                                                                    union {
                                                                                    };
                                                                                  } ;
                                                                                  struct { /* BLOCK ln=86 */
                                                                                    union {
                                                                                      union {
                                                                                      };
                                                                                        struct { /* BLOCK ln=100 */
                                                                                          union {
                                                                                          };
                                                                                        } ;
                                                                                        struct { /* BLOCK ln=86 */
                                                                                          union {
                                                                                            union {
                                                                                            };
                                                                                              struct { /* BLOCK ln=102 */
                                                                                                union {
                                                                                                };
                                                                                              } ;
                                                                                              struct { /* BLOCK ln=86 */
                                                                                                union {
                                                                                                  union {
                                                                                                  };
                                                                                                    struct { /* BLOCK ln=104 */
                                                                                                      union {
                                                                                                      };
                                                                                                    } ;
                                                                                                    struct { /* BLOCK ln=86 */
                                                                                                      union {
                                                                                                        union {
                                                                                                        };
                                                                                                          struct { /* BLOCK ln=106 */
                                                                                                            union {
                                                                                                            };
                                                                                                          } ;
                                                                                                          struct { /* BLOCK ln=86 */
                                                                                                            union {
                                                                                                            };
                                                                                                          } ;
                                                                                                      };
                                                                                                    } ;
                                                                                                };
                                                                                              } ;
                                                                                          };
                                                                                        } ;
                                                                                    };
                                                                                  } ;
                                                                              };
                                                                            } ;
                                                                        };
                                                                      } ;
                                                                  };
                                                                } ;
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                };
                                              } ;
                                          };
                                        } ;
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_Konami;





typedef struct CEU_Growing {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 7 ];
                            struct { /* BLOCK ln=118 */
                              int* gensym;
                              int x;
                              int y;
                              int layer;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=118 */
                                  union {
                                    struct { /* BLOCK ln=126 */
                                    u8 __fin_519_1: 1;
                                      int id;
                                      int water;
                                      union {
                                        union {
                                        };
                                            struct { /* BLOCK ln=130 */
                                              union {
                                              };
                                            } ;
                                        union {
                                        };
                                          struct { /* BLOCK ln=134 */
                                            union {
                                            };
                                          } ;
                                            struct { /* BLOCK ln=136 */
                                              union {
                                              };
                                            } ;
                                            struct { /* BLOCK ln=138 */
                                              union {
                                              };
                                            } ;
                                        struct {
                                          struct { /* BLOCK ln=141 */
                                            union {
                                                struct { /* BLOCK ln=141 */
                                                  struct CEU_Delay _org_386_11;
                                                  union {
                                                        struct { /* BLOCK ln=142 */
                                                          union {
                                                          };
                                                        } ;
                                                    union {
                                                      union {
                                                          struct { /* BLOCK ln=141 */
                                                            union {
                                                            };
                                                          } ;
                                                          struct { /* BLOCK ln=141 */
                                                            union {
                                                            };
                                                          } ;
                                                      };
                                                    };
                                                  };
                                                } ;
                                            };
                                          } ;
                                          struct { /* BLOCK ln=145 */
                                            union {
                                              struct { /* BLOCK ln=145 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=146 */
                                                      union {
                                                          struct { /* BLOCK ln=146 */
                                                            struct CEU_Delay _org_411_12;
                                                            union {
                                                                  struct { /* BLOCK ln=147 */
                                                                    union {
                                                                    };
                                                                  } ;
                                                              union {
                                                                union {
                                                                    struct { /* BLOCK ln=146 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                                    struct { /* BLOCK ln=146 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                                };
                                                              };
                                                            };
                                                          } ;
                                                          struct { /* BLOCK ln=150 */
                                                            union {
                                                                struct { /* BLOCK ln=152 */
                                                                  union {
                                                                  };
                                                                } ;
                                                                  struct { /* BLOCK ln=154 */
                                                                    union {
                                                                    };
                                                                  } ;
                                                                  struct { /* BLOCK ln=156 */
                                                                    union {
                                                                    };
                                                                  } ;
                                                            };
                                                          } ;
                                                          struct { /* BLOCK ln=159 */
                                                            union {
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                          struct { /* BLOCK ln=163 */
                                            union {
                                              struct { /* BLOCK ln=163 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=164 */
                                                      union {
                                                        union {
                                                        };
                                                          struct { /* BLOCK ln=167 */
                                                            union {
                                                            };
                                                          } ;
                                                          struct { /* BLOCK ln=170 */
                                                            union {
                                                            };
                                                          } ;
                                                            struct { /* BLOCK ln=172 */
                                                              union {
                                                              };
                                                            } ;
                                                            struct { /* BLOCK ln=174 */
                                                              union {
                                                              };
                                                            } ;
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                        };
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_Growing;





typedef struct CEU_Philodendron {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 6 ];
                            struct { /* BLOCK ln=188 */
                              int* gensym;
                              struct CEU_Garden* garden;
                              int plot;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=188 */
                                  union {
                                    struct { /* BLOCK ln=193 */
                                    u8 __fin_707_1: 1;
                                      int x;
                                      int y;
                                      int layer;
                                      union {
                                            struct { /* BLOCK ln=195 */
                                              union {
                                              };
                                            } ;
                                        union {
                                        };
                                        union {
                                        };
                                        union {
                                        };
                                        struct {
                                          struct { /* BLOCK ln=201 */
                                            union {
                                              struct { /* BLOCK ln=201 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=202 */
                                                      union {
                                                        union {
                                                          union {
                                                          };
                                                        };
                                                          struct { /* BLOCK ln=204 */
                                                            union {
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                          struct { /* BLOCK ln=209 */
                                            struct CEU_Growing growing_10;
                                            bool survived_11;
                                            union {
                                                  struct { /* BLOCK ln=210 */
                                                    union {
                                                    };
                                                  } ;
                                              union {
                                              };
                                              struct {
                                                struct { /* BLOCK ln=217 */
                                                  union {
                                                    struct { /* BLOCK ln=217 */
                                                      union {
                                                        union {
                                                        };
                                                          struct { /* BLOCK ln=218 */
                                                            union {
                                                              union {
                                                                union {
                                                                };
                                                              };
                                                                struct { /* BLOCK ln=220 */
                                                                  union {
                                                                  };
                                                                } ;
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                  };
                                                } ;
                                                struct { /* BLOCK ln=225 */
                                                  union {
                                                    union {
                                                    };
                                                  };
                                                } ;
                                              };
                                                struct { /* BLOCK ln=228 */
                                                u8 __fin_701_1: 1;
                                                u8 __fin_701_2: 1;
                                                  int id_13;
                                                  union {
                                                        struct { /* BLOCK ln=231 */
                                                          union {
                                                          };
                                                        } ;
                                                    union {
                                                    };
                                                        struct { /* BLOCK ln=238 */
                                                          union {
                                                          };
                                                        } ;
                                                  };
                                                } ;
                                            };
                                          } ;
                                        };
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_Philodendron;





typedef struct CEU_Pitcher {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 6 ];
                            struct { /* BLOCK ln=246 */
                              int* gensym;
                              struct CEU_Garden* garden;
                              int plot;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=246 */
                                  union {
                                    struct { /* BLOCK ln=251 */
                                    u8 __fin_888_1: 1;
                                      int x;
                                      int y;
                                      int layer;
                                      union {
                                            struct { /* BLOCK ln=253 */
                                              union {
                                              };
                                            } ;
                                        union {
                                        };
                                        union {
                                        };
                                        union {
                                        };
                                        struct {
                                          struct { /* BLOCK ln=259 */
                                            union {
                                              struct { /* BLOCK ln=259 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=260 */
                                                      union {
                                                        union {
                                                          union {
                                                          };
                                                        };
                                                          struct { /* BLOCK ln=262 */
                                                            union {
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                          struct { /* BLOCK ln=267 */
                                            struct CEU_Growing growing_10;
                                            bool survived_11;
                                            union {
                                                  struct { /* BLOCK ln=268 */
                                                    union {
                                                    };
                                                  } ;
                                              union {
                                              };
                                              struct {
                                                struct { /* BLOCK ln=275 */
                                                  union {
                                                    struct { /* BLOCK ln=275 */
                                                      union {
                                                        union {
                                                        };
                                                          struct { /* BLOCK ln=276 */
                                                            union {
                                                              union {
                                                                union {
                                                                };
                                                              };
                                                                struct { /* BLOCK ln=278 */
                                                                  union {
                                                                  };
                                                                } ;
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                  };
                                                } ;
                                                struct { /* BLOCK ln=282 */
                                                  union {
                                                    union {
                                                    };
                                                  };
                                                } ;
                                              };
                                                struct { /* BLOCK ln=285 */
                                                u8 __fin_882_1: 1;
                                                u8 __fin_882_2: 1;
                                                  int id_13;
                                                  union {
                                                        struct { /* BLOCK ln=288 */
                                                          union {
                                                          };
                                                        } ;
                                                    union {
                                                    };
                                                        struct { /* BLOCK ln=295 */
                                                          union {
                                                          };
                                                        } ;
                                                  };
                                                } ;
                                            };
                                          } ;
                                        };
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_Pitcher;





typedef struct CEU_Orchid {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 6 ];
                            struct { /* BLOCK ln=303 */
                              int* gensym;
                              struct CEU_Garden* garden;
                              int plot;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=303 */
                                  union {
                                    struct { /* BLOCK ln=308 */
                                    u8 __fin_1069_1: 1;
                                      int x;
                                      int y;
                                      int layer;
                                      union {
                                            struct { /* BLOCK ln=310 */
                                              union {
                                              };
                                            } ;
                                        union {
                                        };
                                        union {
                                        };
                                        union {
                                        };
                                        struct {
                                          struct { /* BLOCK ln=316 */
                                            union {
                                              struct { /* BLOCK ln=316 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=317 */
                                                      union {
                                                        union {
                                                          union {
                                                          };
                                                        };
                                                          struct { /* BLOCK ln=319 */
                                                            union {
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                          struct { /* BLOCK ln=324 */
                                            struct CEU_Growing growing_10;
                                            bool survived_11;
                                            union {
                                                  struct { /* BLOCK ln=325 */
                                                    union {
                                                    };
                                                  } ;
                                              union {
                                              };
                                              struct {
                                                struct { /* BLOCK ln=332 */
                                                  union {
                                                    struct { /* BLOCK ln=332 */
                                                      union {
                                                        union {
                                                        };
                                                          struct { /* BLOCK ln=333 */
                                                            union {
                                                              union {
                                                                union {
                                                                };
                                                              };
                                                                struct { /* BLOCK ln=335 */
                                                                  union {
                                                                  };
                                                                } ;
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                  };
                                                } ;
                                                struct { /* BLOCK ln=339 */
                                                  union {
                                                    union {
                                                    };
                                                  };
                                                } ;
                                              };
                                                struct { /* BLOCK ln=342 */
                                                u8 __fin_1063_1: 1;
                                                u8 __fin_1063_2: 1;
                                                  int id_13;
                                                  union {
                                                        struct { /* BLOCK ln=345 */
                                                          union {
                                                          };
                                                        } ;
                                                    union {
                                                    };
                                                        struct { /* BLOCK ln=352 */
                                                          union {
                                                          };
                                                        } ;
                                                  };
                                                } ;
                                            };
                                          } ;
                                        };
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_Orchid;





typedef struct CEU_Heliconia {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 6 ];
                            struct { /* BLOCK ln=360 */
                              int* gensym;
                              struct CEU_Garden* garden;
                              int plot;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=360 */
                                  union {
                                    struct { /* BLOCK ln=365 */
                                    u8 __fin_1250_1: 1;
                                      int x;
                                      int y;
                                      int layer;
                                      union {
                                            struct { /* BLOCK ln=367 */
                                              union {
                                              };
                                            } ;
                                        union {
                                        };
                                        union {
                                        };
                                        union {
                                        };
                                        struct {
                                          struct { /* BLOCK ln=373 */
                                            union {
                                              struct { /* BLOCK ln=373 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=374 */
                                                      union {
                                                        union {
                                                          union {
                                                          };
                                                        };
                                                          struct { /* BLOCK ln=376 */
                                                            union {
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                          struct { /* BLOCK ln=381 */
                                            struct CEU_Growing growing_10;
                                            bool survived_11;
                                            union {
                                                  struct { /* BLOCK ln=382 */
                                                    union {
                                                    };
                                                  } ;
                                              union {
                                              };
                                              struct {
                                                struct { /* BLOCK ln=389 */
                                                  union {
                                                    struct { /* BLOCK ln=389 */
                                                      union {
                                                        union {
                                                        };
                                                          struct { /* BLOCK ln=390 */
                                                            union {
                                                              union {
                                                                union {
                                                                };
                                                              };
                                                                struct { /* BLOCK ln=392 */
                                                                  union {
                                                                  };
                                                                } ;
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                  };
                                                } ;
                                                struct { /* BLOCK ln=396 */
                                                  union {
                                                    union {
                                                    };
                                                  };
                                                } ;
                                              };
                                                struct { /* BLOCK ln=399 */
                                                u8 __fin_1244_1: 1;
                                                u8 __fin_1244_2: 1;
                                                  int id_13;
                                                  union {
                                                        struct { /* BLOCK ln=402 */
                                                          union {
                                                          };
                                                        } ;
                                                    union {
                                                    };
                                                        struct { /* BLOCK ln=409 */
                                                          union {
                                                          };
                                                        } ;
                                                  };
                                                } ;
                                            };
                                          } ;
                                        };
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_Heliconia;





typedef struct CEU_BagActive {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 4 ];
                            struct { /* BLOCK ln=450 */
                              int id;
                              int* x;
                              int* y;
                              int seed;
                              struct CEU_Garden* garden;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=450 */
                                  union {
                                    struct { /* BLOCK ln=458 */
                                    u8 __fin_1542_1: 1;
                                      int patch;
                                      union {
                                        union {
                                        };
                                            struct { /* BLOCK ln=461 */
                                              union {
                                              };
                                            } ;
                                        struct {
                                          struct { /* BLOCK ln=464 */
                                            union {
                                              union {
                                              };
                                            };
                                          } ;
                                          struct { /* BLOCK ln=466 */
                                            union {
                                              struct { /* BLOCK ln=466 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=467 */
                                                      bool rightborder_10;
                                                      bool leftmidborder_12;
                                                      bool rightmidborder_11;
                                                      bool leftborder_13;
                                                      union {
                                                        union {
                                                        };
                                                        union {
                                                        };
                                                        union {
                                                        };
                                                        union {
                                                        };
                                                          struct { /* BLOCK ln=473 */
                                                            union {
                                                                struct { /* BLOCK ln=474 */
                                                                  union {
                                                                      struct { /* BLOCK ln=475 */
                                                                        union {
                                                                        };
                                                                      } ;
                                                                  };
                                                                } ;
                                                                  struct { /* BLOCK ln=479 */
                                                                    union {
                                                                        struct { /* BLOCK ln=480 */
                                                                          union {
                                                                          };
                                                                        } ;
                                                                    };
                                                                  } ;
                                                                    struct { /* BLOCK ln=484 */
                                                                      union {
                                                                          struct { /* BLOCK ln=485 */
                                                                            union {
                                                                            };
                                                                          } ;
                                                                      };
                                                                    } ;
                                                                    struct { /* BLOCK ln=489 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                            };
                                                          } ;
                                                            struct { /* BLOCK ln=492 */
                                                              union {
                                                                  struct { /* BLOCK ln=493 */
                                                                    union {
                                                                        struct { /* BLOCK ln=494 */
                                                                          union {
                                                                          };
                                                                        } ;
                                                                    };
                                                                  } ;
                                                                    struct { /* BLOCK ln=498 */
                                                                      union {
                                                                          struct { /* BLOCK ln=499 */
                                                                            union {
                                                                            };
                                                                          } ;
                                                                      };
                                                                    } ;
                                                                      struct { /* BLOCK ln=503 */
                                                                        union {
                                                                            struct { /* BLOCK ln=504 */
                                                                              union {
                                                                              };
                                                                            } ;
                                                                        };
                                                                      } ;
                                                                      struct { /* BLOCK ln=508 */
                                                                        union {
                                                                        };
                                                                      } ;
                                                              };
                                                            } ;
                                                        union {
                                                        };
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                        };
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_BagActive;





typedef struct CEU_Bag {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 5 ];
                            struct { /* BLOCK ln=518 */
                              int* gensym;
                              int x;
                              int y;
                              int seed;
                              struct CEU_Garden* garden;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=518 */
                                  union {
                                    struct { /* BLOCK ln=526 */
                                    u8 __fin_1652_1: 1;
                                      int id;
                                      union {
                                        union {
                                        };
                                            struct { /* BLOCK ln=530 */
                                              union {
                                              };
                                            } ;
                                        struct {
                                          struct { /* BLOCK ln=534 */
                                            union {
                                              struct { /* BLOCK ln=534 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=535 */
                                                      union {
                                                        union {
                                                        };
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                          struct { /* BLOCK ln=539 */
                                            union {
                                              struct { /* BLOCK ln=539 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=540 */
                                                      union {
                                                        struct {
                                                          struct { /* BLOCK ln=541 */
                                                            union {
                                                              union {
                                                              };
                                                            };
                                                          } ;
                                                          struct { /* BLOCK ln=544 */
                                                            union {
                                                              union {
                                                              };
                                                            };
                                                          } ;
                                                        };
                                                          struct { /* BLOCK ln=546 */
                                                            struct CEU_BagActive _org_1642_10;
                                                            union {
                                                                  struct { /* BLOCK ln=547 */
                                                                    union {
                                                                    };
                                                                  } ;
                                                              union {
                                                                union {
                                                                    struct { /* BLOCK ln=546 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                                    struct { /* BLOCK ln=546 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                                };
                                                              };
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                        };
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_Bag;





typedef struct CEU_WateringCanActive {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 4 ];
                            struct { /* BLOCK ln=558 */
                              int id;
                              int* x;
                              int* y;
                              struct CEU_Garden* garden;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=558 */
                                  union {
                                    struct { /* BLOCK ln=565 */
                                    u8 __fin_1860_1: 1;
                                      union {
                                            struct { /* BLOCK ln=567 */
                                              union {
                                              };
                                            } ;
                                        struct {
                                          struct { /* BLOCK ln=570 */
                                            union {
                                              union {
                                              };
                                            };
                                          } ;
                                          struct { /* BLOCK ln=572 */
                                            union {
                                              struct { /* BLOCK ln=572 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=573 */
                                                      bool rightborder_8;
                                                      bool leftmidborder_10;
                                                      bool rightmidborder_9;
                                                      bool leftborder_11;
                                                      union {
                                                        union {
                                                        };
                                                        union {
                                                        };
                                                        union {
                                                        };
                                                        union {
                                                        };
                                                          struct { /* BLOCK ln=579 */
                                                            union {
                                                                struct { /* BLOCK ln=580 */
                                                                  union {
                                                                  };
                                                                } ;
                                                                  struct { /* BLOCK ln=582 */
                                                                    union {
                                                                    };
                                                                  } ;
                                                                    struct { /* BLOCK ln=584 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                            };
                                                          } ;
                                                            struct { /* BLOCK ln=587 */
                                                              union {
                                                                  struct { /* BLOCK ln=588 */
                                                                    union {
                                                                    };
                                                                  } ;
                                                                    struct { /* BLOCK ln=590 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                                      struct { /* BLOCK ln=592 */
                                                                        union {
                                                                        };
                                                                      } ;
                                                              };
                                                            } ;
                                                        union {
                                                        };
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                        };
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_WateringCanActive;





typedef struct CEU_WateringCan {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 5 ];
                            struct { /* BLOCK ln=602 */
                              int* gensym;
                              int x;
                              int y;
                              struct CEU_Garden* garden;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=602 */
                                  union {
                                    struct { /* BLOCK ln=609 */
                                    u8 __fin_1964_1: 1;
                                      int id;
                                      union {
                                        union {
                                        };
                                            struct { /* BLOCK ln=613 */
                                              union {
                                              };
                                            } ;
                                        struct {
                                          struct { /* BLOCK ln=617 */
                                            union {
                                              struct { /* BLOCK ln=617 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=618 */
                                                      union {
                                                        union {
                                                        };
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                          struct { /* BLOCK ln=622 */
                                            union {
                                              struct { /* BLOCK ln=622 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=623 */
                                                      union {
                                                        struct {
                                                          struct { /* BLOCK ln=624 */
                                                            union {
                                                              union {
                                                              };
                                                            };
                                                          } ;
                                                          struct { /* BLOCK ln=627 */
                                                            union {
                                                              union {
                                                              };
                                                            };
                                                          } ;
                                                        };
                                                          struct { /* BLOCK ln=629 */
                                                            struct CEU_WateringCanActive _org_1954_9;
                                                            union {
                                                                  struct { /* BLOCK ln=630 */
                                                                    union {
                                                                    };
                                                                  } ;
                                                              union {
                                                                union {
                                                                    struct { /* BLOCK ln=629 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                                    struct { /* BLOCK ln=629 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                                };
                                                              };
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                        };
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_WateringCan;





typedef struct CEU_ShovelActive {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 4 ];
                            struct { /* BLOCK ln=640 */
                              int id;
                              int* x;
                              int* y;
                              struct CEU_Garden* garden;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=640 */
                                  union {
                                    struct { /* BLOCK ln=647 */
                                    u8 __fin_2202_1: 1;
                                      union {
                                            struct { /* BLOCK ln=649 */
                                              union {
                                              };
                                            } ;
                                        struct {
                                          struct { /* BLOCK ln=652 */
                                            union {
                                              union {
                                              };
                                            };
                                          } ;
                                          struct { /* BLOCK ln=654 */
                                            union {
                                              struct { /* BLOCK ln=654 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=655 */
                                                      bool rightborder_8;
                                                      bool leftmidborder_10;
                                                      bool rightmidborder_9;
                                                      bool leftborder_11;
                                                      union {
                                                        union {
                                                        };
                                                        union {
                                                        };
                                                        union {
                                                        };
                                                        union {
                                                        };
                                                          struct { /* BLOCK ln=661 */
                                                            union {
                                                                struct { /* BLOCK ln=662 */
                                                                  union {
                                                                  };
                                                                } ;
                                                                  struct { /* BLOCK ln=665 */
                                                                    union {
                                                                    };
                                                                  } ;
                                                                    struct { /* BLOCK ln=668 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                            };
                                                          } ;
                                                            struct { /* BLOCK ln=672 */
                                                              union {
                                                                  struct { /* BLOCK ln=673 */
                                                                    union {
                                                                    };
                                                                  } ;
                                                                    struct { /* BLOCK ln=676 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                                      struct { /* BLOCK ln=679 */
                                                                        union {
                                                                        };
                                                                      } ;
                                                              };
                                                            } ;
                                                        union {
                                                        };
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                        };
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_ShovelActive;





typedef struct CEU_Shovel {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 5 ];
                            struct { /* BLOCK ln=690 */
                              int* gensym;
                              int x;
                              int y;
                              struct CEU_Garden* garden;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=690 */
                                  union {
                                    struct { /* BLOCK ln=697 */
                                    u8 __fin_2306_1: 1;
                                      int id;
                                      union {
                                        union {
                                        };
                                            struct { /* BLOCK ln=701 */
                                              union {
                                              };
                                            } ;
                                        struct {
                                          struct { /* BLOCK ln=705 */
                                            union {
                                              struct { /* BLOCK ln=705 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=706 */
                                                      union {
                                                        union {
                                                        };
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                          struct { /* BLOCK ln=710 */
                                            union {
                                              struct { /* BLOCK ln=710 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=711 */
                                                      union {
                                                        struct {
                                                          struct { /* BLOCK ln=712 */
                                                            union {
                                                              union {
                                                              };
                                                            };
                                                          } ;
                                                          struct { /* BLOCK ln=715 */
                                                            union {
                                                              union {
                                                              };
                                                            };
                                                          } ;
                                                        };
                                                          struct { /* BLOCK ln=717 */
                                                            struct CEU_ShovelActive _org_2296_9;
                                                            union {
                                                                  struct { /* BLOCK ln=718 */
                                                                    union {
                                                                    };
                                                                  } ;
                                                              union {
                                                                union {
                                                                    struct { /* BLOCK ln=717 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                                    struct { /* BLOCK ln=717 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                                };
                                                              };
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                        };
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_Shovel;





typedef struct CEU_Tween {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 2 ];
                            struct { /* BLOCK ln=728 */
                              int target_x;
                              int target_y;
                              float* x;
                              float* y;
                              int id;
                              float speed;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=728 */
                                  union {
                                    struct { /* BLOCK ln=737 */
                                      union {
                                        struct { /* BLOCK ln=737 */
                                          union {
                                            union {
                                            };
                                              struct { /* BLOCK ln=738 */
                                                float dx_10;
                                                float dy_11;
                                                float dist_12;
                                                union {
                                                    struct { /* BLOCK ln=739 */
                                                      union {
                                                      };
                                                    } ;
                                                  union {
                                                  };
                                                  union {
                                                  };
                                                  union {
                                                  };
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=747 */
                                                      union {
                                                      };
                                                    } ;
                                                    struct { /* BLOCK ln=750 */
                                                      union {
                                                      };
                                                    } ;
                                                    struct { /* BLOCK ln=755 */
                                                      union {
                                                      };
                                                    } ;
                                                    struct { /* BLOCK ln=757 */
                                                      union {
                                                      };
                                                    } ;
                                                };
                                              } ;
                                          };
                                        } ;
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_Tween;





typedef struct CEU_Fly {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 3 ];
                            struct { /* BLOCK ln=763 */
                              int target_x;
                              int target_y;
                              float* x;
                              float* y;
                              int id;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=763 */
                                  union {
                                    struct { /* BLOCK ln=771 */
                                      float speed;
                                      int intermediate_y;
                                      int intermediate_x;
                                      union {
                                        union {
                                        };
                                        union {
                                        };
                                        union {
                                        };
                                          struct { /* BLOCK ln=774 */
                                            struct CEU_Tween _org_2512_12;
                                            union {
                                                  struct { /* BLOCK ln=775 */
                                                    union {
                                                    };
                                                  } ;
                                              union {
                                                union {
                                                    struct { /* BLOCK ln=774 */
                                                      union {
                                                      };
                                                    } ;
                                                    struct { /* BLOCK ln=774 */
                                                      union {
                                                      };
                                                    } ;
                                                };
                                              };
                                            };
                                          } ;
                                          struct { /* BLOCK ln=782 */
                                            struct CEU_Tween _org_2542_13;
                                            union {
                                                  struct { /* BLOCK ln=783 */
                                                    union {
                                                    };
                                                  } ;
                                              union {
                                                union {
                                                    struct { /* BLOCK ln=782 */
                                                      union {
                                                      };
                                                    } ;
                                                    struct { /* BLOCK ln=782 */
                                                      union {
                                                      };
                                                    } ;
                                                };
                                              };
                                            };
                                          } ;
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_Fly;





typedef struct CEU_Seed {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 5 ];
                            struct { /* BLOCK ln=793 */
                              int* gensym;
                              float x;
                              float y;
                              int tier;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=793 */
                                  union {
                                    struct { /* BLOCK ln=799 */
                                    u8 __fin_2741_1: 1;
                                      int id;
                                      bool touched;
                                      union {
                                        union {
                                        };
                                          struct { /* BLOCK ln=804 */
                                            union {
                                            };
                                          } ;
                                            struct { /* BLOCK ln=806 */
                                              union {
                                              };
                                            } ;
                                              struct { /* BLOCK ln=808 */
                                                union {
                                                };
                                              } ;
                                            struct { /* BLOCK ln=812 */
                                              union {
                                              };
                                            } ;
                                        union {
                                        };
                                        struct {
                                          struct { /* BLOCK ln=817 */
                                            union {
                                                struct { /* BLOCK ln=817 */
                                                  struct CEU_Tween _org_2643_9;
                                                  union {
                                                        struct { /* BLOCK ln=818 */
                                                          union {
                                                          };
                                                        } ;
                                                    union {
                                                      union {
                                                          struct { /* BLOCK ln=817 */
                                                            union {
                                                            };
                                                          } ;
                                                          struct { /* BLOCK ln=817 */
                                                            union {
                                                            };
                                                          } ;
                                                      };
                                                    };
                                                  };
                                                } ;
                                            };
                                          } ;
                                          struct { /* BLOCK ln=826 */
                                            union {
                                              struct { /* BLOCK ln=826 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=827 */
                                                      union {
                                                        union {
                                                        };
                                                        union {
                                                        };
                                                          struct { /* BLOCK ln=830 */
                                                            union {
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                        };
                                          struct { /* BLOCK ln=837 */
                                            union {
                                                struct { /* BLOCK ln=837 */
                                                  struct CEU_Tween _org_2720_12;
                                                  union {
                                                        struct { /* BLOCK ln=838 */
                                                          union {
                                                          };
                                                        } ;
                                                    union {
                                                      union {
                                                          struct { /* BLOCK ln=837 */
                                                            union {
                                                            };
                                                          } ;
                                                          struct { /* BLOCK ln=837 */
                                                            union {
                                                            };
                                                          } ;
                                                      };
                                                    };
                                                  };
                                                } ;
                                            };
                                          } ;
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_Seed;





typedef struct CEU_Birb {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 7 ];
                            struct { /* BLOCK ln=857 */
                              int* gensym;
                              int* birb_count;
                              tceu_pool_orgs* seeds;
;
                              int tier;
                              union {
                                  union {
                                  };
                                struct { /* BLOCK ln=857 */
                                  union {
                                    struct { /* BLOCK ln=863 */
                                    u8 __fin_3022_1: 1;
                                      int id;
                                      float y;
                                      float x;
                                      int perched_id;
                                      int texture;
                                      union {
                                        union {
                                        };
                                        union {
                                        };
                                        union {
                                        };
                                        union {
                                        };
                                        union {
                                        };
                                            struct { /* BLOCK ln=873 */
                                              union {
                                              };
                                            } ;
                                        struct {
                                          struct { /* BLOCK ln=880 */
                                            union {
                                              struct { /* BLOCK ln=880 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=881 */
                                                      union {
                                                        union {
                                                        };
                                                          struct { /* BLOCK ln=883 */
                                                            union {
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                          struct { /* BLOCK ln=887 */
                                            union {
                                              struct { /* BLOCK ln=887 */
                                                union {
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=888 */
                                                      int target_perch_12;
                                                      union {
                                                        union {
                                                        };
                                                          struct { /* BLOCK ln=889 */
                                                            struct CEU_Fly _org_2869_13;
                                                            union {
                                                                  struct { /* BLOCK ln=890 */
                                                                    union {
                                                                    };
                                                                  } ;
                                                              union {
                                                                union {
                                                                    struct { /* BLOCK ln=889 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                                    struct { /* BLOCK ln=889 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                                };
                                                              };
                                                            };
                                                          } ;
                                                          struct { /* BLOCK ln=897 */
                                                            union {
                                                            };
                                                          } ;
                                                          struct { /* BLOCK ln=887 */
                                                            union {
                                                                struct { /* BLOCK ln=901 */
                                                                u8 __fin_2945_1: 1;
                                                                  union {
                                                                        struct { /* BLOCK ln=905 */
                                                                          union {
                                                                          };
                                                                        } ;
                                                                      struct { /* BLOCK ln=910 */
                                                                        struct CEU_Delay _org_2943_14;
                                                                        union {
                                                                              struct { /* BLOCK ln=911 */
                                                                                union {
                                                                                };
                                                                              } ;
                                                                          union {
                                                                            union {
                                                                                struct { /* BLOCK ln=910 */
                                                                                  union {
                                                                                  };
                                                                                } ;
                                                                                struct { /* BLOCK ln=910 */
                                                                                  union {
                                                                                  };
                                                                                } ;
                                                                            };
                                                                          };
                                                                        };
                                                                      } ;
                                                                  };
                                                                } ;
                                                            };
                                                          } ;
                                                      };
                                                    } ;
                                                };
                                              } ;
                                            };
                                          } ;
                                        };
                                          struct { /* BLOCK ln=918 */
                                            union {
                                                  struct { /* BLOCK ln=919 */
                                                    union {
                                                    };
                                                  } ;
                                            };
                                          } ;
                                          struct { /* BLOCK ln=926 */
                                            struct CEU_Fly _org_3020_15;
                                            union {
                                                  struct { /* BLOCK ln=927 */
                                                    union {
                                                    };
                                                  } ;
                                              union {
                                                union {
                                                    struct { /* BLOCK ln=926 */
                                                      union {
                                                      };
                                                    } ;
                                                    struct { /* BLOCK ln=926 */
                                                      union {
                                                      };
                                                    } ;
                                                };
                                              };
                                            };
                                          } ;
                                      };
                                    } ;
                                  };
                                } ;
                              };
                            } ;

} CEU_Birb;




typedef struct CEU_Main {
#ifdef CEU_ORGS
  struct tceu_org org;
#endif
  tceu_trl trls_[ 13 ];
    struct { /* BLOCK ln=1 */
      union {
          union {
          };
        struct { /* BLOCK ln=1 */
          union {
              struct { /* BLOCK ln=1 */
                union {
                  union {
                    struct { /* BLOCK ln=1 */
                      tceu_pool_orgs _top_pool;
;
                      int gensym;
                      int birb_count;
                      CEU_Birb* birbs_queue[ 5 ];
CEU_Birb  birbs_mem  [ 5 ];
tceu_pool_orgs birbs;
;
                      CEU_Seed* seeds_queue[ 5 ];
CEU_Seed  seeds_mem  [ 5 ];
tceu_pool_orgs seeds;
;
                      struct CEU_Garden garden;
                      union {
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                        };
                        union {
                              struct { /* BLOCK ln=939 */
                                union {
                                };
                              } ;
                        };
                        struct {
                          struct { /* BLOCK ln=942 */
                            union {
                              struct { /* BLOCK ln=942 */
                                union {
                                  union {
                                  };
                                    struct { /* BLOCK ln=943 */
                                      union {
                                        struct { /* BLOCK ln=943 */
                                          union {
                                            union {
                                            };
                                              struct { /* BLOCK ln=944 */
                                                union {
                                                  union {
                                                  };
                                                  union {
                                                  };
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=948 */
                                                      union {
                                                      };
                                                    } ;
                                                };
                                              } ;
                                          };
                                        } ;
                                        struct { /* BLOCK ln=952 */
                                          union {
                                            union {
                                            };
                                              struct { /* BLOCK ln=953 */
                                                union {
                                                  union {
                                                  };
                                                  union {
                                                  };
                                                  union {
                                                  };
                                                    struct { /* BLOCK ln=957 */
                                                      union {
                                                      };
                                                    } ;
                                                };
                                              } ;
                                          };
                                        } ;
                                      };
                                    } ;
                                };
                              } ;
                            };
                          } ;
                          struct { /* BLOCK ln=963 */
                            union {
                              struct { /* BLOCK ln=963 */
                                union {
                                  union {
                                  };
                                    struct { /* BLOCK ln=964 */
                                      int seed_11;
                                      int plot_12;
                                      union {
                                        union {
                                        };
                                        union {
                                        };
                                          struct { /* BLOCK ln=967 */
                                            union {
                                            };
                                          } ;
                                          struct { /* BLOCK ln=969 */
                                            union {
                                                struct { /* BLOCK ln=970 */
                                                  union {
                                                        struct { /* BLOCK ln=971 */
                                                          union {
                                                          };
                                                        } ;
                                                  };
                                                } ;
                                                  struct { /* BLOCK ln=976 */
                                                    union {
                                                          struct { /* BLOCK ln=977 */
                                                            union {
                                                            };
                                                          } ;
                                                    };
                                                  } ;
                                                    struct { /* BLOCK ln=984 */
                                                      union {
                                                            struct { /* BLOCK ln=985 */
                                                              union {
                                                              };
                                                            } ;
                                                      };
                                                    } ;
                                                      struct { /* BLOCK ln=992 */
                                                        union {
                                                              struct { /* BLOCK ln=993 */
                                                                union {
                                                                };
                                                              } ;
                                                        };
                                                      } ;
                                            };
                                          } ;
                                      };
                                    } ;
                                };
                              } ;
                            };
                          } ;
                          struct { /* BLOCK ln=1003 */
                            union {
                              struct { /* BLOCK ln=1003 */
                                union {
                                  union {
                                  };
                                    struct { /* BLOCK ln=1004 */
                                      union {
                                        struct {
                                          struct { /* BLOCK ln=1006 */
                                            union {
                                              union {
                                              };
                                            };
                                          } ;
                                          struct { /* BLOCK ln=1008 */
                                            int x_13;
                                            int y_14;
                                            union {
                                              union {
                                              };
                                              union {
                                              };
                                                struct { /* BLOCK ln=1011 */
                                                  union {
                                                      struct { /* BLOCK ln=1012 */
                                                        union {
                                                            struct { /* BLOCK ln=1012 */
                                                              struct CEU_Shovel _org_3374_15;
                                                              union {
                                                                    struct { /* BLOCK ln=1013 */
                                                                      union {
                                                                      };
                                                                    } ;
                                                                union {
                                                                  union {
                                                                      struct { /* BLOCK ln=1012 */
                                                                        union {
                                                                        };
                                                                      } ;
                                                                      struct { /* BLOCK ln=1012 */
                                                                        union {
                                                                        };
                                                                      } ;
                                                                  };
                                                                };
                                                              };
                                                            } ;
                                                        };
                                                      } ;
                                                        struct { /* BLOCK ln=1019 */
                                                          union {
                                                              struct { /* BLOCK ln=1019 */
                                                                struct CEU_WateringCan _org_3417_16;
                                                                union {
                                                                      struct { /* BLOCK ln=1020 */
                                                                        union {
                                                                        };
                                                                      } ;
                                                                  union {
                                                                    union {
                                                                        struct { /* BLOCK ln=1019 */
                                                                          union {
                                                                          };
                                                                        } ;
                                                                        struct { /* BLOCK ln=1019 */
                                                                          union {
                                                                          };
                                                                        } ;
                                                                    };
                                                                  };
                                                                };
                                                              } ;
                                                          };
                                                        } ;
                                                          struct { /* BLOCK ln=1026 */
                                                            union {
                                                                struct { /* BLOCK ln=1026 */
                                                                  struct CEU_Bag _org_3464_17;
                                                                  union {
                                                                        struct { /* BLOCK ln=1027 */
                                                                          union {
                                                                          };
                                                                        } ;
                                                                    union {
                                                                      union {
                                                                          struct { /* BLOCK ln=1026 */
                                                                            union {
                                                                            };
                                                                          } ;
                                                                          struct { /* BLOCK ln=1026 */
                                                                            union {
                                                                            };
                                                                          } ;
                                                                      };
                                                                    };
                                                                  };
                                                                } ;
                                                            };
                                                          } ;
                                                            struct { /* BLOCK ln=1034 */
                                                              union {
                                                                  struct { /* BLOCK ln=1035 */
                                                                    union {
                                                                        struct { /* BLOCK ln=1035 */
                                                                          struct CEU_Bag _org_3516_18;
                                                                          union {
                                                                                struct { /* BLOCK ln=1036 */
                                                                                  union {
                                                                                  };
                                                                                } ;
                                                                            union {
                                                                              union {
                                                                                  struct { /* BLOCK ln=1035 */
                                                                                    union {
                                                                                    };
                                                                                  } ;
                                                                                  struct { /* BLOCK ln=1035 */
                                                                                    union {
                                                                                    };
                                                                                  } ;
                                                                              };
                                                                            };
                                                                          };
                                                                        } ;
                                                                    };
                                                                  } ;
                                                              };
                                                            } ;
                                                              struct { /* BLOCK ln=1044 */
                                                                union {
                                                                    struct { /* BLOCK ln=1045 */
                                                                      union {
                                                                          struct { /* BLOCK ln=1045 */
                                                                            struct CEU_Bag _org_3571_19;
                                                                            union {
                                                                                  struct { /* BLOCK ln=1046 */
                                                                                    union {
                                                                                    };
                                                                                  } ;
                                                                              union {
                                                                                union {
                                                                                    struct { /* BLOCK ln=1045 */
                                                                                      union {
                                                                                      };
                                                                                    } ;
                                                                                    struct { /* BLOCK ln=1045 */
                                                                                      union {
                                                                                      };
                                                                                    } ;
                                                                                };
                                                                              };
                                                                            };
                                                                          } ;
                                                                      };
                                                                    } ;
                                                                };
                                                              } ;
                                                                struct { /* BLOCK ln=1054 */
                                                                  union {
                                                                      struct { /* BLOCK ln=1055 */
                                                                        union {
                                                                            struct { /* BLOCK ln=1055 */
                                                                              struct CEU_Bag _org_3626_20;
                                                                              union {
                                                                                    struct { /* BLOCK ln=1056 */
                                                                                      union {
                                                                                      };
                                                                                    } ;
                                                                                union {
                                                                                  union {
                                                                                      struct { /* BLOCK ln=1055 */
                                                                                        union {
                                                                                        };
                                                                                      } ;
                                                                                      struct { /* BLOCK ln=1055 */
                                                                                        union {
                                                                                        };
                                                                                      } ;
                                                                                  };
                                                                                };
                                                                              };
                                                                            } ;
                                                                        };
                                                                      } ;
                                                                  };
                                                                } ;
                                                  };
                                                } ;
                                            };
                                          } ;
                                        };
                                      };
                                    } ;
                                };
                              } ;
                            };
                          } ;
                          struct { /* BLOCK ln=1068 */
                            union {
                              struct { /* BLOCK ln=1068 */
                                union {
                                  union {
                                  };
                                    struct { /* BLOCK ln=1069 */
                                      union {
                                        union {
                                        };
                                          struct { /* BLOCK ln=1071 */
                                            union {
                                                  struct { /* BLOCK ln=1072 */
                                                    union {
                                                    };
                                                  } ;
                                            };
                                          } ;
                                      };
                                    } ;
                                };
                              } ;
                            };
                          } ;
                          struct { /* BLOCK ln=1080 */
                            union {
                              struct { /* BLOCK ln=1080 */
                                union {
                                  union {
                                  };
                                    struct { /* BLOCK ln=1081 */
                                      union {
                                        union {
                                        };
                                          struct { /* BLOCK ln=1083 */
                                            union {
                                                  struct { /* BLOCK ln=1084 */
                                                    union {
                                                    };
                                                  } ;
                                            };
                                          } ;
                                      };
                                    } ;
                                };
                              } ;
                            };
                          } ;
                          struct { /* BLOCK ln=1092 */
                            union {
                              struct { /* BLOCK ln=1092 */
                                union {
                                  union {
                                  };
                                    struct { /* BLOCK ln=1093 */
                                      union {
                                        union {
                                        };
                                          struct { /* BLOCK ln=1095 */
                                            union {
                                                  struct { /* BLOCK ln=1096 */
                                                    union {
                                                    };
                                                  } ;
                                            };
                                          } ;
                                      };
                                    } ;
                                };
                              } ;
                            };
                          } ;
                        };
                      };
                    } ;
                  };
                };
              } ;
          };
        } ;
      };
    } ;

} CEU_Main;






#endif
