#ifndef RENDERERGL44_RENDERTHREAD_H
#define RENDERERGL44_RENDERTHREAD_H


#if !defined(__APPLE__) && !defined(__ANDROID__)
#include <QObject>
#include <QImage>
#include <QWindow>
#if !defined(__APPLE__) && !defined(__ANDROID__)
//#include <QtPlatformSupport/QtPlatformSupport>
#endif
#include "renderdoc_app.h"
#include "abstractrenderer.h"
//#include "GFSDK_SSAO.h"

class RendererGL44_RenderThread : public QObject, public AbstractRenderer
{
    Q_OBJECT

public:
    RendererGL44_RenderThread();
    virtual ~RendererGL44_RenderThread();

    virtual void Initialize();
    virtual void Render(std::unordered_map<size_t, std::vector<AbstractRenderCommand>> * p_scoped_render_commands,
                        std::unordered_map<StencilReferenceValue, LightContainer> * p_scoped_light_containers);
    virtual void PreRender(std::unordered_map<size_t, std::vector<AbstractRenderCommand> > * p_scoped_render_commands,
                           std::unordered_map<StencilReferenceValue, LightContainer> * p_scoped_light_containers);
    virtual void PostRender(std::unordered_map<size_t, std::vector<AbstractRenderCommand> > * p_scoped_render_commands,
                            std::unordered_map<StencilReferenceValue, LightContainer> * p_scoped_light_containers);
    virtual void UpgradeShaderSource(QByteArray & p_shader_source, bool p_is_vertex_shader);

    void SaveScreenshot();   

public slots:

    void PrintFPS();
    void InitializeGLContext(QOpenGLContext* p_gl_context);
    void CreateMeshHandleForGeomVBODataMIRRORCOPY(AbstractRenderer * p_main_thread_renderer, GeomVBOData * p_VBO_data);
    void CreateMeshHandle(AbstractRenderer * p_main_thread_renderer, std::shared_ptr<MeshHandle> * p_handle,
                            VertexAttributeLayout p_layout);
    void Process(AbstractRenderer * p_main_thread_renderer, std::unordered_map<size_t, std::vector<AbstractRenderCommand>> * p_scoped_object_render_commands, std::unordered_map<StencilReferenceValue, LightContainer> * p_scoped_light_containers);
    void InitializeGLObjectsMIRROR(AbstractRenderer * p_renderer);
    void DecoupledRender();
    void FinishThread();

signals:

    void Finished();
    void Error(QString err);

private:

    void UpdatePerObjectData(std::unordered_map<size_t, std::vector<AbstractRenderCommand> > * p_scoped_render_commands);
    void UpdatePerObjectSSBO(std::unordered_map<size_t, std::vector<AbstractRenderCommand> > * p_scoped_render_commands, const bool p_using_instancing = false);

    void RenderEqui();

    PersistentGLBuffer<static_cast<uint32_t>(BUFFER_CHUNK_COUNT), 1> m_per_object_buffer;
    PersistentGLBuffer<static_cast<uint32_t>(BUFFER_CHUNK_COUNT), 2> m_per_instance_buffer;
    PersistentGLBuffer<static_cast<uint32_t>(BUFFER_CHUNK_COUNT), 3> m_per_camera_buffer;
    PersistentGLBuffer<static_cast<uint32_t>(BUFFER_CHUNK_COUNT), 4> m_per_material_buffer;
    std::vector<AssetShader_Material> m_material_dictionary;
    std::vector<PerObjectSSBOData> m_per_object_data;
    std::vector<PerMaterialSSBOData> m_per_material_data;
    std::vector<PerInstanceSSBOData> m_per_instance_data;
    std::vector<PerCameraSSBOData> m_per_camera_data;
    std::vector<int> m_camera_to_camera_SSBO;
    GLint m_max_compute_work_groups;
    QOffscreenSurface *  m_gl_surface;
    QOpenGLContext * m_gl_context;
    QOpenGLFunctions_4_4_Core * m_gl_funcs;
    GLuint m_main_thread_fbo;
    std::shared_ptr<TextureHandle> m_equi_cubemap_handle;
    uint32_t m_equi_cubemap_face_size;

    bool m_is_rendering;
    bool m_is_initialized;
    bool m_hmd_initialized;
    bool m_capture_frame;
    QThread* m_thread;
    QTimer m_timer;
    QTimer m_fps_timer;
    qint64  m_frame_time;
    AbstractRenderer * m_main_thread_renderer;
    bool m_screenshot_pbo_pending;
    GLuint m_screenshot_pbo;
    bool m_frame_vector_sorted;
    bool m_object_buffer_dirty;
    bool m_material_buffer_dirty;
    bool m_camera_buffer_dirty;

    std::vector<AbstractRenderCommand_sort> m_sorted_command_indices;
    bool m_shutting_down;
};
#endif
#endif // RendererGL44_RenderThread_H
