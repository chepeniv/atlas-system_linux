# c lang constructors and destructors with gcc

these are special functions commonly provided in OOP languages and typically
defined within an object class. they contain initialization and cleanup code
required for an object to operate correctly and are automatically called when
an object is created or destroyed. multiple constructors may be defined for an
object for which the correct one is automatically selected by the compiler.

these do not exist in c or in structured languages in general, yet there are
no limitations on creating such functions although they need to be called
manually.

## gcc constructor and destructor attributes

gcc provides attributes which notify the compiler about how certain things
should be handled. among these are function attributes used to define
constructors and destructors in c. these __only__ work under gcc. a function
defined as a constructor would run before `main()` starts, whereas a destructor
would execute after `main()` has concluded

```c
__attribute__((constructor))
__attribute__((destructor))
__attribute__((constructor (PRIORITY)))
__attribute__((destructor (PRIORITY)))

/* example */

void begin(void) __attributeS__((constructor));
void end(void) __attributeS__((destructor));

/* alternatively */

__attribute__((constructor)) void begin(void)
{ /* func body */ }

__attribute__((destructor)) void end(void)
{ /* func body */ }
```

## multiple constructors and destructors

with multiple constructors and destructors being defined, they are automatically
executed dependent on their priority given. constructors with _lower values_ are
executed first, whereas destructors with _higher values_ are executed first

attempting to compile with priority values between 0 and 100 inclusively throws
warnings since they are reserved for implementation (might be used internally).
it is the relative values of the `PRIORITY` parameter, and not its absolute,
that determines the sequence of execution.

before `main()` there's a startup function which prepares the environment for
execution. this is the function that calls the given constructors and
destructors before and after `main()`. within the executable the sections which
hold these user-defined constructors and destructors are `.ctors` and `.dtors`
respectively
