/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org

Copyright (c) 2000-2014 Torus Knot Software Ltd
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef _ShaderProgramWriterGLSL_
#define _ShaderProgramWriterGLSL_

#include "OgreShaderProgramWriterManager.h"
#include "OgreShaderProgramWriter.h"
#include "OgreShaderParameter.h"
#include "OgreStringVector.h"

namespace Ogre {
namespace RTShader {

    class Function;
    class Program;

/** \addtogroup Optional
*  @{
*/
/** \addtogroup RTShader
*  @{
*/

/** GLSL target language writer implementation.
@see ProgramWriter.
*/
class GLSLProgramWriter : public ProgramWriter
{
    // Interface.
public:

    /** Class constructor. 
    */
    GLSLProgramWriter();

    /** Class destructor */
    virtual ~GLSLProgramWriter();


    /** 
    @see ProgramWriter::writeSourceCode.
    */
    virtual void writeSourceCode(std::ostream& os, Program* program);

    /** 
    @see ProgramWriter::getTargetLanguage.
    */
    virtual const String& getTargetLanguage() const { return TargetLanguage; }

    static String TargetLanguage;

    // Protected methods.
protected:

    void writeMainSourceCode(std::ostream& os, Program* program);

    /** Initialize string maps. */
    void initializeStringMaps();

    /** Write a local parameter. */
    void writeLocalParameter(std::ostream& os, ParameterPtr parameter);

    /** Write the program dependencies. */
    void writeProgramDependencies(std::ostream& os, Program* program);

    /** Write the input params of the function */
    void writeInputParameters(std::ostream& os, Function* function, GpuProgramType gpuType);
    
    /** Write the output params of the function */
    void writeOutParameters(std::ostream& os, Function* function, GpuProgramType gpuType);

protected:
    typedef std::map<GpuConstantType, const char*>     GpuConstTypeToStringMap;
    typedef std::map<Parameter::Semantic, const char*> ParamSemanticToStringMap;
    typedef std::map<Parameter::Content, const char*>  ParamContentToStringMap;
    typedef std::map<String, String>                   StringMap;

    // Attributes.
protected:
    // Map between GPU constant type to string value.
    GpuConstTypeToStringMap mGpuConstTypeMap;
    // Map between parameter semantic to string value.
    ParamSemanticToStringMap mParamSemanticMap;

    std::set<String> mLocalRenames;

    // Map parameter content to vertex attributes 
    ParamContentToStringMap mContentToPerVertexAttributes;
    // Holds the current glsl version
    int mGLSLVersion;
    // set by derived class
    bool mIsGLSLES;
};

/** GLSL program writer factory implementation.
@see ProgramWriterFactory
*/
class ShaderProgramWriterGLSLFactory : public ProgramWriterFactory
{
public:
    ShaderProgramWriterGLSLFactory() : mLanguage("glsl")
    {
    }
    virtual ~ShaderProgramWriterGLSLFactory() {}

    /** 
    @see ProgramWriterFactory::getTargetLanguage
    */
    virtual const String& getTargetLanguage(void) const
    {
        return mLanguage;
    }

    /** 
    @see ProgramWriterFactory::create
    */
    virtual ProgramWriter* create(void)
    {
        return OGRE_NEW GLSLProgramWriter();
    }

private:
    String mLanguage;

};

/** @} */
/** @} */

}
}

#endif
