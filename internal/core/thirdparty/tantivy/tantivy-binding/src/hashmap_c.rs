use std::collections::HashMap;
use std::os::raw::c_char;

use libc::c_void;

use crate::util::{c_ptr_to_str, create_binding, free_binding};

#[no_mangle]
pub extern "C" fn create_hashmap() -> *mut c_void {
    let map: HashMap<String, String> = HashMap::new();
    create_binding(map)
}

#[no_mangle]
pub extern "C" fn hashmap_set_value(map: *mut c_void, key: *const c_char, value: *const c_char) {
    let m = map as *mut HashMap<String, String>;
    let k = c_ptr_to_str(key).unwrap();
    let v = c_ptr_to_str(value).unwrap();
    unsafe {
        (*m).insert(String::from(k), String::from(v));
    }
}

#[no_mangle]
pub extern "C" fn free_hashmap(map: *mut c_void) {
    free_binding::<HashMap<String, String>>(map);
}
