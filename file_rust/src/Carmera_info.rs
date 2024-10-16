// Automatically generated rust module for 'Carmera_info.proto' file

#![allow(non_snake_case)]
#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(unused_imports)]
#![allow(unknown_lints)]
#![allow(clippy::all)]
#![cfg_attr(rustfmt, rustfmt_skip)]


use std::borrow::Cow;
use quick_protobuf::{MessageInfo, MessageRead, MessageWrite, BytesReader, Writer, WriterBackend, Result};
use quick_protobuf::sizeofs::*;
use super::*;

#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Debug, Default, PartialEq, Clone)]
pub struct image_info<'a> {
    pub name: Cow<'a, str>,
    pub Make: Cow<'a, str>,
    pub Model: Cow<'a, str>,
    pub ExposureTime: Cow<'a, str>,
    pub StandardOutputSensitivity: Cow<'a, str>,
    pub ExposureProgram: Cow<'a, str>,
    pub FNumber: Cow<'a, str>,
}

impl<'a> MessageRead<'a> for image_info<'a> {
    fn from_reader(r: &mut BytesReader, bytes: &'a [u8]) -> Result<Self> {
        let mut msg = Self::default();
        while !r.is_eof() {
            match r.next_tag(bytes) {
                Ok(10) => msg.name = r.read_string(bytes).map(Cow::Borrowed)?,
                Ok(18) => msg.Make = r.read_string(bytes).map(Cow::Borrowed)?,
                Ok(26) => msg.Model = r.read_string(bytes).map(Cow::Borrowed)?,
                Ok(34) => msg.ExposureTime = r.read_string(bytes).map(Cow::Borrowed)?,
                Ok(42) => msg.StandardOutputSensitivity = r.read_string(bytes).map(Cow::Borrowed)?,
                Ok(50) => msg.ExposureProgram = r.read_string(bytes).map(Cow::Borrowed)?,
                Ok(58) => msg.FNumber = r.read_string(bytes).map(Cow::Borrowed)?,
                Ok(t) => { r.read_unknown(bytes, t)?; }
                Err(e) => return Err(e),
            }
        }
        Ok(msg)
    }
}

impl<'a> MessageWrite for image_info<'a> {
    fn get_size(&self) -> usize {
        0
        + if self.name == "" { 0 } else { 1 + sizeof_len((&self.name).len()) }
        + if self.Make == "" { 0 } else { 1 + sizeof_len((&self.Make).len()) }
        + if self.Model == "" { 0 } else { 1 + sizeof_len((&self.Model).len()) }
        + if self.ExposureTime == "" { 0 } else { 1 + sizeof_len((&self.ExposureTime).len()) }
        + if self.StandardOutputSensitivity == "" { 0 } else { 1 + sizeof_len((&self.StandardOutputSensitivity).len()) }
        + if self.ExposureProgram == "" { 0 } else { 1 + sizeof_len((&self.ExposureProgram).len()) }
        + if self.FNumber == "" { 0 } else { 1 + sizeof_len((&self.FNumber).len()) }
    }

    fn write_message<W: WriterBackend>(&self, w: &mut Writer<W>) -> Result<()> {
        if self.name != "" { w.write_with_tag(10, |w| w.write_string(&**&self.name))?; }
        if self.Make != "" { w.write_with_tag(18, |w| w.write_string(&**&self.Make))?; }
        if self.Model != "" { w.write_with_tag(26, |w| w.write_string(&**&self.Model))?; }
        if self.ExposureTime != "" { w.write_with_tag(34, |w| w.write_string(&**&self.ExposureTime))?; }
        if self.StandardOutputSensitivity != "" { w.write_with_tag(42, |w| w.write_string(&**&self.StandardOutputSensitivity))?; }
        if self.ExposureProgram != "" { w.write_with_tag(50, |w| w.write_string(&**&self.ExposureProgram))?; }
        if self.FNumber != "" { w.write_with_tag(58, |w| w.write_string(&**&self.FNumber))?; }
        Ok(())
    }
}

