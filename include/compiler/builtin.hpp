#if defined(__GNUC__)
#define LIKELY(x) __builtin_expect(x, 1)
#define UNLIKELY(x) __builtin_expect(x, 0)
#define PREFETCH(x) __builtin_prefetch(x)
#define ALLLOC_STACK_SIZE(x) __builtin_alloca(x)
#else
#define LIKELY(x) x
#define UNLIKELY(x) x
#define PREFETCH(x)
#endif